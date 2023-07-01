#pragma once
#include "SFML/Graphics.hpp"
#include "display/ui.hpp"
#include "logic/gameLogic.hpp"
#include <future>
#include <queue>

/*

There are 3 threads:
1. main thread
   this thread is responsible for the window. It initiates
   draw calls at 60hz and polls for window events at 1khz.
   these events are pushes onto one of the local queues.
2. display thread
   this thread loops at 1khz. It looks for window events on the 
   main queues and acts on them. Eg. a mouseUp event may result
   in a button being pushed (so long as a mouseDown was previously
   on that button). If a button on the UI has been pushed it may
   push an event onto one of the gameLogic queues
3. logic thread
   this thread is responsible for all game logic and calculations.
   It stores all of its data in the observableData class for reading
   by the display thread.

synchronization:
there are 3 global mutex's:
1. ui_mutex
   this is located in this file. Both the main thread and the display thread
   access ui elements and must stay synchronized (X11 gets very upset if you don't)
2. data_mutex
   this is located in the ObservableData global struct. 
     - While the UI is rendered, the Ui class will hold this mutex. Note that it is
       the main thread that orders this, not the display thread.
     - While in the gameTick function the GameLogic class will hold this mutex
3. gametick_mutex
   this is located in the EventInterface global struct
     - while an item in the Ui is queuing an event that item will hold this mutex
     - while in the handleEvents function (called from gameTick) the GameLogic class
       will hold this mutex

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
   void charEntered();
   void backspace();

   bool init_od;

   bool m_window_resized;
   std::queue<sf::Vector2i> m_ev_mouse_moved;
   std::queue<sf::Vector2i> m_ev_mouse_down;
   std::queue<sf::Vector2i> m_ev_mouse_up;
   int m_ev_backspace;
   std::queue<char> m_ev_char_entered;

   sf::Cursor m_cursor;

   std::future<void> m_ui_thread;
   std::future<void> m_gametick_thread;
   mutable std::mutex m_ui_mutex;
   sf::RenderWindow m_window;
   Ui m_ui; 
   GameLogic m_game_logic;
};

} // namespace Game
