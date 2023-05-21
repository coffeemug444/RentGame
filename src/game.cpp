#include "game.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace std::this_thread;

namespace Game
{

Game::Game()
:m_window(sf::VideoMode(400, 400), "Rent game")
,m_ui(*this, m_window.getSize())
{
   m_cursor.loadFromSystem(sf::Cursor::Arrow);
   m_window.setMouseCursor(m_cursor);
}

void Game::resizeWindow()
{
   if (not m_window_resized) return;
   m_window_resized = false;
   float width = static_cast<float>(m_window.getSize().x);
   float height = static_cast<float>(m_window.getSize().y);
   m_window.setView(sf::View(sf::FloatRect{0.f,0.f,width, height}));
   m_ui.setScreenSize(m_window.getSize());
}

void Game::mouseMoved()
{
   while (m_ev_mouse_moved.size() > 0)
   {
      sf::Vector2i mouse_pos = m_ev_mouse_moved.front();
      m_ev_mouse_moved.pop_front();

      if (mouse_pos.x < 0 || mouse_pos.y < 0) return;
      
      auto window_size = m_window.getSize();
      if (mouse_pos.x > window_size.x) return;
      if (mouse_pos.y > window_size.y) return;

      auto cursor_type = m_ui.mouseMoved(mouse_pos);
      m_cursor.loadFromSystem(cursor_type);
      m_window.setMouseCursor(m_cursor);
   }
}

void Game::mouseDown()
{
   while (m_ev_mouse_down.size() > 0)
   {
      sf::Vector2i mouse_pos = m_ev_mouse_down.front();
      m_ev_mouse_down.pop_front();

      m_ui.mouseDown(mouse_pos);
   }
}

void Game::mouseUp()
{
   while (m_ev_mouse_up.size() > 0)
   {
      sf::Vector2i mouse_pos = m_ev_mouse_up.front();
      m_ev_mouse_up.pop_front();
      
      m_ui.mouseUp(mouse_pos);
      m_ev_mouse_moved.push_back(mouse_pos);
   }
}


void Game::pollEvents()
{
   sf::Event event;
   while (m_window.pollEvent(event))
   {
      switch (event.type)
      {
      case sf::Event::Closed:
         {std::lock_guard lock(m_gametick_mutex);
         m_game_logic.stop();
         }
         break;
      case sf::Event::Resized:
         m_window_resized = true;
         break;
      case sf::Event::MouseMoved:
         m_ev_mouse_moved.push_back({event.mouseMove.x,event.mouseMove.y});
         break;
      case sf::Event::MouseButtonPressed:
         if (event.mouseButton.button != sf::Mouse::Button::Left) break;
         m_ev_mouse_down.push_back({event.mouseButton.x,event.mouseButton.y});
         break;
      case sf::Event::MouseButtonReleased:
         if (event.mouseButton.button != sf::Mouse::Button::Left) break;
         m_ev_mouse_up.push_back({event.mouseButton.x,event.mouseButton.y});
         break;
      default:
         break;
      }
   }
}

// not to be called from the gameLogic loop
bool Game::gameRunning()
{
   {std::lock_guard lock(m_gametick_mutex);
   return m_game_logic.running();
   }
}

void Game::uiLoop()
{
   while (1)
   {
      {std::lock_guard lock(m_ui_mutex);
      if (not gameRunning()) break;
      resizeWindow();
      mouseMoved();
      mouseDown();
      mouseUp();
      } // mutex lock
      sleep_for(1ms);
   }
}

void Game::gametickLoop()
{
   while (1)
   {
      {std::lock_guard lock(m_gametick_mutex);
      if (not m_game_logic.running()) break;
      m_game_logic.gameTick();
      } // mutex lock
      sleep_for(50ms); // 20hz gameticks
   }
}

void Game::mainLoop()
{
   m_ui_thread = std::async(&Game::uiLoop, this);
   m_gametick_thread = std::async(&Game::gametickLoop, this);
   sf::Clock timer;

   // 1/60 seconds in microseconds, delay time for 60fps
   sf::Int64 ds = 16667;

   sf::Int64 last_time = timer.getElapsedTime().asMicroseconds() - ds - 1;

   while (1)
   {
      {std::lock_guard lock(m_ui_mutex);
      if (not gameRunning()) break;

      pollEvents();
      sf::Int64 current_time = timer.getElapsedTime().asMicroseconds();
      if (current_time - last_time < ds) continue;
      last_time = current_time;

      m_window.clear();
      // draw scene
      m_window.draw(m_ui);
      m_window.display();
      } // mutex lock
      sleep_for(1ms);
   }

   m_ui_thread.wait();
   m_gametick_thread.wait();

   m_window.close();
}

} // namespace Game
