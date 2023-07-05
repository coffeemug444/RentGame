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
      return TICKS_PER_SEC / 2;
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
      m_current_speed = EI::ev_gamespeed_changed.front();
      clear(EI::ev_gamespeed_changed);

      OD::current_speed = m_current_speed;
   }

   while (EI::ev_take_loan.size() > 0)
   {
      auto loan = EI::ev_take_loan.front();
      // check if it's ok

      // yep all those checks LGTM
      OD::Player::loans.push_back({ loan.principal, 
                                    loan.interest_rate_yearly / 12.f, 
                                    loan.repayment_time_months });
      OD::Player::capital += loan.principal;
      OD::Player::debt += loan.principal;
      EI::ev_take_loan_status.push(SUCCESS);

      EI::ev_take_loan.pop();
   }

   while (EI::ev_purchase_property.size() > 0)
   {
      auto purchase_order = EI::ev_purchase_property.front();
      if (OD::market.purchaseListing(purchase_order.listing_id))
      {
         EI::ev_purchase_property.pop();
      }
   }

   while (EI::ev_change_monitored_property_id.size() > 0)
   {
      OD::monitored_property_id = EI::ev_change_monitored_property_id.front();
      EI::ev_change_monitored_property_id.pop();
   }
}

void GameLogic::advanceDay()
{
   OD::Date::day++;

   for (auto& loan : OD::Player::loans)
   {
      loan.advanceDay();
   }
   for (auto& property : OD::Player::properties)
   {
      property.advanceDay();
   }

   OD::market.advanceDay();

   int loan_total = 0;
   for (Loan& loan : OD::Player::loans)
   {
      loan_total += loan.getAmount();
   }

   OD::Player::debt = loan_total;
}

void GameLogic::gameTick()
{
   if (not OD::game_running) return;

   handleEvents();

   if (m_current_speed == PAUSE) return;


   m_current_day_ticks++;

   if (m_current_day_ticks < gameSpeedTicks(m_current_speed)) return;
   
   m_current_day_ticks -= gameSpeedTicks(m_current_speed);
   advanceDay(); // called last
   
}

} // namespace Game