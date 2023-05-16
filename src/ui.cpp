#include "ui.hpp"
#include "util.hpp"



Ui::Ui(Game& game, sf::Vector2u screen_size)
:m_game(game)
,m_screen_size(screen_size)
{
   m_toolbar.setSize(screen_size * sf::Vector2f{1, 0.1f});
   m_toolbar.setFillColor(sf::Color{0xf2d666ff});
   m_toolbar.setPosition(screen_size * sf::Vector2f{0, 0.9f});
}

void Ui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   std::lock_guard lock(m_data_mutex);
   target.draw(m_toolbar);
}