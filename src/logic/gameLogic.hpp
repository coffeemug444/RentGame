#pragma once

namespace Game 
{

class GameLogic
{
public:
   GameLogic() : m_stopgame(false), m_running(true) {}
   void advanceDay() { if (m_stopgame) m_running = false; }
   bool running() { return m_running; }
   void stop () { m_stopgame = true; }
private:
   bool m_stopgame;
   bool m_running;
};


} // namespace Game