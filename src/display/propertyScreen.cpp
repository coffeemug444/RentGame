#include "propertyScreen.hpp"
#include "ui.hpp"

namespace Game
{

PropertyScreen::PropertyScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Property", sf::Color(OD::property_color))
,m_individual_property_screen_open(false)
,m_individual_property_screen_button(*this, &PropertyScreen::individualPropertyScreenButtonCallback)
,m_individual_property_screen(ui, screen_size)
{
   m_individual_property_screen_button.setFillColor(sf::Color::Red);
   m_individual_property_screen_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);
}

sf::Cursor::Type PropertyScreen::getCursorType(sf::Vector2i mouse_pos) const
{
   if (m_individual_property_screen_open)
   {
      return m_individual_property_screen.getCursorType(mouse_pos);
   }
   return m_individual_property_screen_button.mouseIsOver(mouse_pos)
          ? sf::Cursor::Hand
          : sf::Cursor::Arrow;
}

void PropertyScreen::mouseDown(sf::Vector2i mouse_pos) 
{
   if (m_individual_property_screen_open)
   {
      return m_individual_property_screen.mouseDown(mouse_pos);
   }

   if (m_individual_property_screen_button.mouseIsOver(mouse_pos))
   {
      m_individual_property_screen_button.click();
   }
}

void PropertyScreen::mouseUp(sf::Vector2i mouse_pos) 
{

}

void PropertyScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
   if (not m_active) return;
   
   if (m_individual_property_screen_open)
   {
      target.draw(m_individual_property_screen);
      return;
   }

   Screen::draw(target, states);
   target.draw(m_individual_property_screen_button);

}

void PropertyScreen::individualPropertyScreenButtonCallback()
{
   m_individual_property_screen_open = true;
   m_individual_property_screen.setActive(true);
}

void PropertyScreen::setScreenSize(sf::Vector2u screen_size) 
{
   Screen::setScreenSize(screen_size);
   m_individual_property_screen.setScreenSize(screen_size);
   m_individual_property_screen_button.setPosition({screen_size.x-2*m_individual_property_screen_button.getRadius(),0});
}

void PropertyScreen::setActive(bool active) 
{
   Screen::setActive(active);
   m_individual_property_screen_open = false;
   m_individual_property_screen.setActive(false);
}


} // namespace Game