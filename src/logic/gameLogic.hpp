#pragma once

namespace Game 
{

enum GameSpeed {
   PAUSED,
   HALF_SPEED,
   NORMAL_SPEED,
   DOUBLE_SPEED
};

class GameLogic
{
public:
   GameLogic();
   void gameTick();
   bool running() const { return m_running; }
   void stop () { m_stopgame = true; }
   void changeSpeed(GameSpeed new_speed);

private:
   static inline const int TICKS_PER_SEC = 20;

   constexpr int gameSpeedTicks(GameSpeed speed) const;

   void advanceDay() {};
   int m_current_day_ticks;
   GameSpeed m_current_speed;
   bool m_paused;
   bool m_stopgame;
   bool m_running;
};


} // namespace Game