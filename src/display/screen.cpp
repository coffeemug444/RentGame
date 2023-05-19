#include "screen.hpp"
#include "button.hpp"

namespace Game
{


Screen::Screen(Ui& ui, sf::Vector2u screen_size, std::string title, sf::Color background_color, std::vector<Button*> buttons)
:m_ui(ui)
,m_screen_size(screen_size)
,m_background_color(background_color) 
,m_active(false) 
,m_buttons(buttons)
{
   setScreenSize(screen_size);
   m_background.setFillColor(background_color);

   m_font.loadFromFile("font/Rubik-VariableFont_wght.ttf");
   m_title.setFont(m_font);
   m_title.setString(title);
}

sf::Cursor::Type Screen::getCursorType(sf::Vector2i mouse_pos) const
{
   for (auto button_ptr : m_buttons)
   {
      if (button_ptr->mouseIsOver(mouse_pos)) return sf::Cursor::Hand;
   }
   return sf::Cursor::Arrow;
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
}




} // namespace Game
