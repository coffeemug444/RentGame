#include "screen.hpp"
#include "display/widgets/widget.hpp"
#include "observableData.hpp"

namespace Game
{

Screen::Screen(std::string title, sf::Color background_color, Widget::PlacementStyle style)
:Widget(style)
,m_background_color(background_color) 
,m_title(title)
,m_active(false) 
{
   m_background.setFillColor(background_color);
}

void Screen::setSize(const sf::Vector2f& screen_size)
{
   Widget::setSize(screen_size);
   m_background.setSize(screen_size);
}


void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (not m_active) return;
   target.draw(m_background);
   Widget::draw(target, states);
}


} // namespace Game
