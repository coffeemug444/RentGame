#include "game.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace std::this_thread;

namespace Game
{

Game::Game()
:m_window(sf::VideoMode(800, 800), "Rent game")
,m_ui(*this, m_window.getSize())
{
}

void Game::closeWindow()
{
   std::lock_guard lock(m_window_mutex);
   m_window.close();
}

void Game::pollEvents()
{
   sf::Event event;
   while (m_window.pollEvent(event))
   {
      switch (event.type)
      {
      case sf::Event::Closed:
         closeWindow();
         break;
      default:
         break;
      }
   }
}

void Game::displayLoop()
{
   while (1)
   {
      {
      std::lock_guard lock(m_window_mutex);

      if (not m_window.isOpen()) return;
      
      m_window.clear();

      // draw scene
      m_window.draw(m_ui);

      m_window.display();
      }

      sleep_for(16ms);
   }
}

void Game::mainLoop()
{
   m_display_thread = std::async(&Game::displayLoop, this);
   while (m_window.isOpen())
   {
      pollEvents();
   }

   m_display_thread.wait();
}

}
