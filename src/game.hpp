#pragma once
#include "SFML/Graphics.hpp"
#include "display/ui.hpp"
#include <future>

namespace Game
{

class Game
{
public:
   Game();
   void mainLoop();
   void setCursor(sf::Cursor::Type cursor_type);
private:
   void displayLoop();
   void pollEvents();
   void closeWindow();
   void resizeWindow();
   void mouseMoved(sf::Vector2i mouse_pos);
   std::future<void> m_display_thread;
   mutable std::mutex m_window_mutex;
   sf::RenderWindow m_window;
   Ui m_ui;
};

} // namespace Game
