#include "game.hpp"

Game::Game()
:m_window(sf::VideoMode(800, 800), "Rent game")
,m_ui(*this, m_window.getSize())
{
}

void Game::pollEvents()
{
   sf::Event event;
   while (m_window.pollEvent(event))
   {
      switch (event.type)
      {
      case sf::Event::Closed:
         m_window.close();
         break;
      default:
         break;
      }
   }
}

void Game::displayLoop()
{
   while (m_window.isOpen())
   {
      m_window.clear();

      // draw scene
      m_window.draw(m_ui);

      m_window.display();
   }
}

void Game::mainLoop()
{
   m_display_thread = std::async(&Game::displayLoop, this);
   while (m_window.isOpen())
   {
      pollEvents();
   }
}