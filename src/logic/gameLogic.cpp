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

   while (EI::ev_purchase_listing_id.size() > 0)
   {
      if (OD::market.purchaseListing(EI::ev_purchase_listing_id.front()))
      {
         EI::ev_purchase_listing_id.pop();
      }
   }

   while (EI::ev_change_monitored_property_id.size() > 0)
   {
      OD::monitored_property_id = EI::ev_change_monitored_property_id.front();
      EI::ev_change_monitored_property_id.pop();
   }

   while (EI::ev_set_property_managed_status.size() > 0)
   {
      auto ev = EI::ev_set_property_managed_status.front();
      EI::ev_set_property_managed_status.pop();
      if (not listContainsId(ev.property_id, OD::Player::properties))
         continue;
      auto& property = *findById(ev.property_id, OD::Player::properties).value();
      property.setManaged(ev.managed);
   }

   while (EI::ev_update_property_prices.size() > 0)
   {
      auto ev = EI::ev_update_property_prices.front();
      EI::ev_update_property_prices.pop();
      if (not listContainsId(ev.property_id, OD::Player::properties))
         continue;
      auto& property = *findById(ev.property_id, OD::Player::properties).value();
      property.setPrice(ev.sale_price);
      property.setRentalPrice(ev.rental_price);
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