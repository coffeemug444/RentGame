#include "ui.hpp"
#include "util/util.hpp"
#include "game.hpp"
#include "observableData.hpp"

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

void Ui::selectScreen(ToolbarScreen screen)
{
   if (screen == m_selected_screen) return;
   
   switch (m_selected_screen)
   {
   case FINANCE:
      m_finance_screen.setActive(false);
      break;
   case PROPERTIES:
      m_property_screen.setActive(false);
      break;
   case LOANS:
      m_loan_screen.setActive(false);
      break;
   case MARKET:
      m_market_screen.setActive(false);
      break;
   }

   m_selected_screen = screen;
   switch (screen)
   {
   case FINANCE:
      m_finance_screen.setActive(true);
      break;
   case PROPERTIES:
      m_property_screen.setActive(true);
      break;
   case LOANS:
      m_loan_screen.setActive(true);
      break;
   case MARKET:
      m_market_screen.setActive(true);
      break;
   }
}


sf::Cursor::Type Ui::mouseMoved(sf::Vector2u mouse_pos) const
{
   return m_toolbar.getCursorType(mouse_pos);
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
