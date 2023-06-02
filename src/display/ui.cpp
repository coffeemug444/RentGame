#include "ui.hpp"
#include "util/util.hpp"
#include "game.hpp"
#include "observableData.hpp"
#include <iostream>

namespace Game
{

Ui::Ui(Game& game, sf::Vector2u screen_size)
:m_game(game)
,m_screen_size(screen_size)
,m_selected_screen(FINANCE)
,m_toolbar(*this, screen_size)
,m_loan_screen(*this, screen_size)
,m_finance_screen(*this, screen_size)
,m_property_screen(*this, screen_size)
,m_market_screen(*this, screen_size)
,m_current_cursor(sf::Cursor::Arrow)
,m_screen_map{
   {FINANCE, &m_finance_screen},
   {PROPERTIES, &m_property_screen},
   {LOANS, &m_loan_screen},
   {MARKET, &m_market_screen}
}
{
   m_finance_screen.setActive(true);
}

void Ui::setScreenSize(sf::Vector2u screen_size)
{
   m_loan_screen.setScreenSize(screen_size);
   m_finance_screen.setScreenSize(screen_size);
   m_property_screen.setScreenSize(screen_size);
   m_market_screen.setScreenSize(screen_size);
   m_toolbar.setScreenSize(screen_size);
}

void Ui::selectScreen(MainScreen screen)
{
   if (screen == m_selected_screen) return;

   m_screen_map[m_selected_screen]->setActive(false);
   m_screen_map[screen]->setActive(true);
   m_selected_screen = screen;
}


sf::Cursor::Type Ui::mouseMoved(sf::Vector2i mouse_pos) const
{
   if (m_toolbar.mouseIsOver(mouse_pos)) 
   {
      return m_toolbar.getCursorType(mouse_pos);
   }

   switch(m_selected_screen)
   {
      case FINANCE:
         return m_finance_screen.getCursorType(mouse_pos);
      case PROPERTIES:
         return m_property_screen.getCursorType(mouse_pos);
      case LOANS:
         return m_loan_screen.getCursorType(mouse_pos);
      case MARKET:
         return m_market_screen.getCursorType(mouse_pos);
   }

   return sf::Cursor::Arrow;
}

void Ui::mouseDown(sf::Vector2i mouse_pos)
{
   if (m_toolbar.mouseIsOver(mouse_pos)) 
   {
      return m_toolbar.mouseDown(mouse_pos);
   }

   switch(m_selected_screen)
   {
      case FINANCE:
         return m_finance_screen.mouseDown(mouse_pos);
      case PROPERTIES:
         return m_property_screen.mouseDown(mouse_pos);
      case LOANS:
         return m_loan_screen.mouseDown(mouse_pos);
      case MARKET:
         return m_market_screen.mouseDown(mouse_pos);
   }
}


void Ui::mouseUp(sf::Vector2i mouse_pos)
{
   m_toolbar.mouseUp(mouse_pos);
   m_finance_screen.mouseUp(mouse_pos);
   m_property_screen.mouseUp(mouse_pos);
   m_loan_screen.mouseUp(mouse_pos);
   m_market_screen.mouseUp(mouse_pos);
}

void Ui::charEntered(char c) 
{
   m_finance_screen.charEntered(c);
   m_property_screen.charEntered(c);
   m_loan_screen.charEntered(c);
   m_market_screen.charEntered(c);
}

void Ui::backspace() 
{
   m_finance_screen.backspace();
   m_property_screen.backspace();
   m_loan_screen.backspace();
   m_market_screen.backspace();
}


void Ui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   std::lock_guard lock(OD::data_mutex);
   target.draw(m_loan_screen);
   target.draw(m_finance_screen);
   target.draw(m_property_screen);
   target.draw(m_market_screen);
   target.draw(m_toolbar);
}

} // namespace Game
