#include "ui.hpp"
#include "util/util.hpp"
#include "game.hpp"
#include "observableData.hpp"

namespace Game
{

Ui::Ui(Game& game, sf::Vector2u screen_size)
:m_game(game)
,m_screen_size(screen_size)
,m_toolbar(*this, screen_size)
,m_loan_screen(*this, screen_size)
,m_finance_screen(*this, screen_size)
,m_property_screen(*this, screen_size)
,m_market_screen(*this, screen_size)
,m_current_cursor(sf::Cursor::Arrow)
{
}

void Ui::setScreenSize(sf::Vector2u screen_size)
{
   m_loan_screen.setScreenSize(screen_size);
   m_finance_screen.setScreenSize(screen_size);
   m_property_screen.setScreenSize(screen_size);
   m_market_screen.setScreenSize(screen_size);
   m_toolbar.setScreenSize(screen_size);
}


void Ui::mouseMoved(sf::Vector2u mouse_pos)
{
   sf::Cursor::Type bar_type = m_toolbar.getCursorType(mouse_pos);

   m_game.setCursor(bar_type);
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
