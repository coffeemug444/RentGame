#include "screen.hpp"
#include "display/widgets/widget.hpp"
#include "observableData.hpp"

namespace Game
{

Screen::Screen(std::string title, sf::Color background_color, Widget::PlacementStyle style)
:Widget(style)
,m_background_color(background_color) 
,m_active(false) 
{
   m_background.setFillColor(background_color);

   m_title.setFont(OD::font);
   m_title.setString(title);
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
   target.draw(m_title);

   Widget::draw(target, states);
}


} // namespace Game
