#include "screen.hpp"
#include "display/buttons/button.hpp"
#include "display/widgets/widget.hpp"

#include <iostream>
namespace Game
{

Screen::Screen(Ui& ui, sf::Vector2u screen_size, std::string title, sf::Color background_color, const std::vector<Button*>& buttons, const std::vector<Widget*>& widgets)
:Widget(buttons, widgets)
,m_ui(ui)
,m_widgets(widgets)
,m_screen_size(screen_size)
,m_background_color(background_color) 
,m_active(false) 
,m_last_button_id(0)
{
   setScreenSize(screen_size);
   m_background.setFillColor(background_color);

   m_font.loadFromFile("font/Rubik-VariableFont_wght.ttf");
   m_title.setFont(m_font);
   m_title.setString(title);
}
void Screen::setScreenSize(sf::Vector2u screen_size)
{
   float screen_w = static_cast<float>(screen_size.x);
   float screen_h = static_cast<float>(screen_size.y);
   m_background.setSize({screen_w,screen_h});
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (not m_active) return;

   target.draw(m_background);
   target.draw(m_title);

   Widget::draw(target, states);
}


void Screen::mouseDown(sf::Vector2i mouse_pos)
{
   if (not m_active)
   {
      m_last_button_id = 0;
      return;
   }
   Widget::mouseDown(mouse_pos);
}

void Screen::mouseUp(sf::Vector2i mouse_pos)
{
   if (not m_active)
   {
      m_last_button_id = 0;
      return;
   }
   Widget::mouseUp(mouse_pos);
}





} // namespace Game
