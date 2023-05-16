#pragma once
#include "SFML/Graphics.hpp"
#include "ui.hpp"
#include <future>

class Game
{
public:
   Game();
   void mainLoop();
private:
   void displayLoop();
   void pollEvents();
   std::future<void> m_display_thread;
   sf::RenderWindow m_window;
   Ui m_ui;
};