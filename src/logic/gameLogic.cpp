#include "gameLogic.hpp"

namespace Game
{

GameLogic::GameLogic()
:m_current_day_ticks(0)
,m_current_speed(PAUSE)
,m_paused(false)
,m_stopgame(false)
,m_running(true) 
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

void GameLogic::gameTick()
{
   if (m_stopgame) 
   {
      m_running = false;
      return;
   }
   if (m_current_speed == PAUSE) return;


   m_current_day_ticks++;

   if (m_current_day_ticks < gameSpeedTicks(m_current_speed)) return;
   
   m_current_day_ticks -= gameSpeedTicks(m_current_speed);
   advanceDay();
   
}

} // namespace Game