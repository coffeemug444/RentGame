#pragma once
#include "SFML/Graphics.hpp"
#include "display/ui.hpp"
#include "logic/gameLogic.hpp"
#include <future>
#include <deque>

/*

Main executing thread must be the one to poll the window. This includes events
and draw calls. This diagram shows which loops access which mutexes. From what
I understand you need a loop of mutex calls for deadlock to occur, and there 
are no loops in this diagram so I think this is safe.

               main loop
                 +->-+
                 |   |
                 +---+ 
game loop           \     ui loop
  +->-+              \     +->-+  
  |   |               ---->|   |
  |   |<-------------------|   |
  |   |                    |   |
  +---+   +------------+   +---+  
    \     | observable |     /      
     ---->|   data     |<----
          +------------+

*/    


namespace Game
{

class Game
{
public:
   Game();
   void mainLoop();
private:
   bool gameRunning();  // not to be called from the gameLogic loop
   void uiLoop();
   void gametickLoop();
   void pollEvents();
   void closeWindow();
   void resizeWindow();
   void mouseMoved();
   void mouseDown();
   void mouseUp();

   bool m_window_resized;
   std::deque<sf::Vector2i> m_ev_mouse_moved;
   std::deque<sf::Vector2i> m_ev_mouse_down;
   std::deque<sf::Vector2i> m_ev_mouse_up;

   sf::Cursor m_cursor;

   std::future<void> m_ui_thread;
   std::future<void> m_gametick_thread;
   mutable std::mutex m_ui_mutex;
   mutable std::mutex m_gametick_mutex;
   sf::RenderWindow m_window;
   Ui m_ui; 
   GameLogic m_game_logic;
};

} // namespace Game
