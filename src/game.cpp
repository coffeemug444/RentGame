#include "game.hpp"

Game::Game()
:m_window(sf::VideoMode(200, 200), "Rent game")
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

void Game::loop()
{
   while (m_window.isOpen())
   {
      pollEvents();
      m_window.clear();

      // draw scene

      m_window.display();
   }
}