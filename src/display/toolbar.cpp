#include "toolbar.hpp"
#include "util/util.hpp"

namespace Game
{

Toolbar::Toolbar(Ui& ui, sf::Vector2u screen_size)
:m_ui(ui)
,m_screen_size(screen_size)
{
   m_bar.setSize(screen_size * sf::Vector2f{1, 0.1f});
   m_bar.setFillColor(sf::Color{0xf2d666ff});
   m_bar.setPosition(screen_size * sf::Vector2f{0, 0.9f});
}

void Toolbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_bar);
}

} // namespace Game