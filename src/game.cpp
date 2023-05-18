#include "game.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace std::this_thread;

namespace Game
{

Game::Game()
:m_cursor_type(sf::Cursor::Arrow)
,m_window(sf::VideoMode(400, 400), "Rent game")
,m_ui(*this, m_window.getSize())
{
}

void Game::closeWindow()
{
   std::lock_guard lock(m_ui_mutex);
   m_window.close();
}

void Game::resizeWindow()
{
   std::lock_guard lock(m_ui_mutex);
   float width = static_cast<float>(m_window.getSize().x);
   float height = static_cast<float>(m_window.getSize().y);
   m_window.setView(sf::View(sf::FloatRect{0.f,0.f,width, height}));
   m_ui.setScreenSize(m_window.getSize());
}

void Game::mouseMoved(sf::Vector2i mouse_pos)
{
   if (mouse_pos.x < 0 || mouse_pos.y < 0) return;
   
   auto window_size = m_window.getSize();
   if (mouse_pos.x > window_size.x) return;
   if (mouse_pos.y > window_size.y) return;

   std::lock_guard lock(m_ui_mutex);
   auto cursor_type = m_ui.mouseMoved(mouse_pos);
   if (m_cursor_type == cursor_type) return;
   m_cursor_type = cursor_type;
   sf::Cursor cursor;
   cursor.loadFromSystem(cursor_type);
   m_window.setMouseCursor(cursor);
}

void Game::mouseDown(sf::Vector2i mouse_pos)
{
   m_ui.mouseDown(mouse_pos);
}

void Game::mouseUp(sf::Vector2i mouse_pos)
{
   m_ui.mouseUp(mouse_pos);
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
      case sf::Event::Resized:
         resizeWindow();
         break;
      case sf::Event::MouseMoved:
         mouseMoved({event.mouseMove.x,event.mouseMove.y});
         break;
      case sf::Event::MouseButtonPressed:
         if (event.mouseButton.button != sf::Mouse::Button::Left) break;
         mouseDown({event.mouseButton.x,event.mouseButton.y});
         break;
      case sf::Event::MouseButtonReleased:
         if (event.mouseButton.button != sf::Mouse::Button::Left) break;
         mouseDown({event.mouseButton.x,event.mouseButton.y});
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
      { std::lock_guard lock(m_ui_mutex);

      if (not m_window.isOpen()) return;
      
      m_window.clear();

      // draw scene
      m_window.draw(m_ui);

      m_window.display();

      } // end mutex lock
   
      sleep_for(16ms);
   }
}

void Game::mainLoop()
{
   m_display_thread = std::async(&Game::displayLoop, this);
   while (1)
   {
      {std::lock_guard lock(m_ui_mutex);

      if (not m_window.isOpen()) break;
      }
      pollEvents();
   }

   m_display_thread.wait();
}

} // namespace Game
