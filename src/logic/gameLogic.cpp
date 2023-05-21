#include "gameLogic.hpp"

namespace Game
{

GameLogic::GameLogic()
:m_current_day_ticks(0)
,m_current_speed(PAUSED)
,m_paused(false)
,m_stopgame(false)
,m_running(true) 
{
}

constexpr int GameLogic::gameSpeedTicks(GameSpeed speed) const
{
   switch(speed)
   {
   case PAUSED:
      return 0;
   case HALF_SPEED:
      return TICKS_PER_SEC * 2;
   case NORMAL_SPEED:
      return TICKS_PER_SEC;
   case DOUBLE_SPEED:
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
   if (m_current_speed == PAUSED) return;


   m_current_day_ticks++;

   if (m_current_day_ticks < gameSpeedTicks(m_current_speed)) return;
   
   m_current_day_ticks -= gameSpeedTicks(m_current_speed);
   advanceDay();
   
}

} // namespace Game