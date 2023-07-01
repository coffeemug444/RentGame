#pragma once

namespace Game 
{



class GameLogic
{
public:
   enum GameSpeed {
      PAUSE,
      NORMAL,
      FAST,
      VERYFAST
   };
   
   GameLogic();
   void gameTick();
   void changeSpeed(GameSpeed new_speed);

private:
   static inline const int TICKS_PER_SEC = 20;

   constexpr int gameSpeedTicks(GameSpeed speed) const;
   void handleEvents();

   void advanceDay();
   int m_current_day_ticks;
   GameSpeed m_current_speed;
};


} // namespace Game