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

void Ui::selectScreen(ToolbarScreen screen)
{
   if (screen == m_selected_screen) return;

   m_screen_map[m_selected_screen]->setActive(false);
   m_screen_map[screen]->setActive(true);
   m_selected_screen = screen;
}


sf::Cursor::Type Ui::mouseMoved(sf::Vector2i mouse_pos) const
{
   auto [toolbar_valid, cursor_type] = m_toolbar.getCursorType(mouse_pos);
   return cursor_type;
}

void Ui::mouseDown(sf::Vector2i mouse_pos)
{
   m_toolbar.mouseDown(mouse_pos);
}

void Ui::mouseUp(sf::Vector2i mouse_pos)
{
   m_toolbar.mouseUp(mouse_pos);
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
