#include "gameLogic.hpp"
#include "eventInterface.hpp"
#include "observableData.hpp"

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
      EI::ev_stop_game.clear();
   }

   if (EI::ev_gamespeed_changed.size() > 0)
   {
      m_current_speed = EI::ev_gamespeed_changed.back();
      EI::ev_gamespeed_changed.clear();

      OD::current_speed = m_current_speed;
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