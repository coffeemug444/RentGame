#include "gameLogic.hpp"
#include "events/eventInterface.hpp"
#include "observableData.hpp"
#include "util/util.hpp"

namespace Game
{

GameLogic::GameLogic()
:m_current_day_ticks(0)
,m_current_speed(PAUSE)
{
}

constexpr int GameLogic::gameSpeedTicks(GameSpeed speed) const
{
   switch(speed)
   {
   case PAUSE:
      return 0;
   case NORMAL:
      return TICKS_PER_SEC * 2;
   case FAST:
      return TICKS_PER_SEC;
   case VERYFAST:
      return TICKS_PER_SEC;
   }
   return 0;
}

void GameLogic::handleEvents()
{
   std::lock_guard lock(EI::gametick_mutex);

   if (EI::ev_stop_game.size() > 0)
   {
      OD::game_running = false;
      clear(EI::ev_stop_game);
   }

   if (EI::ev_gamespeed_changed.size() > 0)
   {
      m_current_speed = EI::ev_gamespeed_changed.back();
      clear(EI::ev_gamespeed_changed);

      OD::current_speed = m_current_speed;
   }

   while (EI::ev_loan_monthly_payment_arrears.size() > 0)
   {
      auto ev = EI::ev_loan_monthly_payment.front();
      EI::ev_loan_monthly_payment.pop();

      if (ev.amount > OD::Player::capital)
      {
         OD::game_running = false; // fix this
      }
      else
      {
         auto loan = findById(ev.loan_id, OD::Player::loans);
         if (loan.has_value()) loan.value()->pay(ev.amount);
      }
   }

   while (EI::ev_take_loan.size() > 0)
   {
      auto loan = EI::ev_take_loan.front();
      // check if it's ok

      // yep all those checks LGTM
      OD::Player::loans.push_back({ loan.principal, 
                                    loan.interest_rate_yearly / 12.f, 
                                    loan.repayment_time_months, 
                                    OD::Player::next_loan_id });
      std::cout << "taking loan with loan_id " << OD::Player::next_loan_id << std::endl;
      OD::Player::next_loan_id++;
      EI::ev_take_loan_status.push(SUCCESS);

      EI::ev_take_loan.pop();
   }
}

void GameLogic::gameTick()
{
   if (not OD::game_running) return;

   handleEvents();

   if (m_current_speed == PAUSE) return;


   m_current_day_ticks++;

   if (m_current_day_ticks < gameSpeedTicks(m_current_speed)) return;
   
   m_current_day_ticks -= gameSpeedTicks(m_current_speed);
   advanceDay();
   
}

} // namespace Game