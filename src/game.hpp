#pragma once
#include "SFML/Graphics.hpp"
#include "display/ui.hpp"
#include <future>

/*

Only set the ui mutex when making changes to the window object, and ensure
it's released immediately after. Methods like `mouseUp` and `mouseDown` may
eventually go to methods that change the window object, but the mutex gets
grabbed there, otherwise the program will deadlock

*/


namespace Game
{

class Game
{
public:
   Game();
   void mainLoop();
private:
   void displayLoop();
   void pollEvents();
   void closeWindow();
   void resizeWindow();
   void mouseMoved(sf::Vector2i mouse_pos);
   void mouseDown(sf::Vector2i mouse_pos);
   void mouseUp(sf::Vector2i mouse_pos);
   std::future<void> m_display_thread;
   mutable std::mutex m_ui_mutex;
   sf::Cursor::Type m_cursor_type;
   sf::RenderWindow m_window;
   Ui m_ui;
};

} // namespace Game
