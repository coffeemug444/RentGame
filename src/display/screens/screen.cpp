#include "screen.hpp"
#include "display/widgets/widget.hpp"
#include "observableData.hpp"

namespace Game
{

Screen::Screen(Ui& ui, sf::Vector2u screen_size, std::string title, sf::Color background_color)
:m_ui(ui)
,m_screen_size(screen_size)
,m_background_color(background_color) 
,m_active(false) 
{
   m_background.setFillColor(background_color);

   m_title.setFont(OD::font);
   m_title.setString(title);
}
void Screen::setScreenSize(sf::Vector2u screen_size)
{
   float screen_w = static_cast<float>(screen_size.x);
   float screen_h = static_cast<float>(screen_size.y);
   m_background.setSize({screen_w,screen_h});
   for (auto& widget : *this)
   {
      widget.setScreenSize(screen_size);
   }
}

sf::Vector2f Screen::getSize() const
{
   return m_background.getSize();
}

sf::Vector2f Screen::getPosition() const
{
   return m_background.getPosition();
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (not m_active) return;

   target.draw(m_background);
   target.draw(m_title);

   Widget::draw(target, states);
}


} // namespace Game
