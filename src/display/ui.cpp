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
,m_bank_screen(*this, screen_size)
,m_individual_property_screen(*this, screen_size)
,m_current_cursor(sf::Cursor::Arrow)
,m_screen_map{
   {FINANCE, &m_finance_screen},
   {PROPERTIES, &m_property_screen},
   {LOANS, &m_loan_screen},
   {MARKET, &m_market_screen},
   {BANK, &m_bank_screen},
   {INDIVIDUAL_PROPERTY, &m_individual_property_screen}
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
   m_bank_screen.setScreenSize(screen_size);
   m_individual_property_screen.setScreenSize(screen_size);
   m_toolbar.setScreenSize(screen_size);
}

void Ui::selectScreen(MainScreen screen)
{
   if (screen == m_selected_screen) return;

   m_screen_map[m_selected_screen]->setActive(false);
   m_screen_map[screen]->setActive(true);
   m_selected_screen = screen;
}

const Screen& Ui::getSelectedScreen() const
{
   switch(m_selected_screen)
   {
      case FINANCE:
         return m_finance_screen;
      case PROPERTIES:
         return m_property_screen;
      case LOANS:
         return m_loan_screen;
      case MARKET:
         return m_market_screen;
      case BANK:
         return m_bank_screen;
      case INDIVIDUAL_PROPERTY:
         return m_individual_property_screen;
      default: throw -1;
   }
}

Screen& Ui::getSelectedScreen()
{
   switch(m_selected_screen)
   {
      case FINANCE:
         return m_finance_screen;
      case PROPERTIES:
         return m_property_screen;
      case LOANS:
         return m_loan_screen;
      case MARKET:
         return m_market_screen;
      case BANK:
         return m_bank_screen;
      case INDIVIDUAL_PROPERTY:
         return m_individual_property_screen;
      default: throw -1;
   }
}

sf::Cursor::Type Ui::mouseMoved(sf::Vector2i mouse_pos) const
{
   if (m_toolbar.mouseIsOver(mouse_pos)) 
   {
      return m_toolbar.getCursorType(mouse_pos);
   }

   return getSelectedScreen().getCursorType(mouse_pos);
}

void Ui::mouseDown(sf::Vector2i mouse_pos)
{
   if (m_toolbar.mouseIsOver(mouse_pos)) 
   {
      return m_toolbar.mouseDown(mouse_pos);
   }

   return getSelectedScreen().mouseDown(mouse_pos);
}


void Ui::mouseUp(sf::Vector2i mouse_pos)
{
   m_toolbar.mouseUp(mouse_pos);
   m_finance_screen.mouseUp(mouse_pos);
   m_property_screen.mouseUp(mouse_pos);
   m_loan_screen.mouseUp(mouse_pos);
   m_market_screen.mouseUp(mouse_pos);
   m_bank_screen.mouseUp(mouse_pos);
   m_individual_property_screen.mouseUp(mouse_pos);
}

void Ui::charEntered(char c) 
{
   getSelectedScreen().charEntered(c);
}

void Ui::backspace() 
{
   getSelectedScreen().backspace();
}


void Ui::uiEvents()
{
   m_finance_screen.uiEvents();
   m_property_screen.uiEvents();
   m_loan_screen.uiEvents();
   m_market_screen.uiEvents();
   m_bank_screen.uiEvents();
   m_individual_property_screen.uiEvents();
}

void Ui::dataSync()
{
   m_finance_screen.dataSync();
   m_property_screen.dataSync();
   m_loan_screen.dataSync();
   m_market_screen.dataSync();
   m_bank_screen.dataSync();
   m_individual_property_screen.dataSync();
}


void Ui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   std::lock_guard lock(OD::data_mutex);
   target.draw(getSelectedScreen());
   target.draw(m_toolbar);
}

} // namespace Game
