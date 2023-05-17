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
private:
   void displayLoop();
   void pollEvents();
   void closeWindow();
   std::future<void> m_display_thread;
   mutable std::mutex m_window_mutex;
   sf::RenderWindow m_window;
   Ui m_ui;
};

} // namespace Game
