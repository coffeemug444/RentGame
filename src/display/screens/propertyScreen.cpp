#include "propertyScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"


namespace Game
{

PropertyScreen::PropertyScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Property", CC::property_color, {&m_individual_property_screen_button})
,m_individual_property_screen_button(*this, INDIVIDUAL)
,m_individual_property_screen(ui, *this, screen_size)
{
   m_individual_property_screen_button.setFillColor(CC::individual_property_color);
   m_individual_property_screen_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);
}

sf::Cursor::Type PropertyScreen::getCursorType(sf::Vector2i mouse_pos) const
{
   if (m_individual_property_screen.getActive())
   {
      return m_individual_property_screen.getCursorType(mouse_pos);
   }
   return Screen::getCursorType(mouse_pos);
}

void PropertyScreen::mouseDown(sf::Vector2i mouse_pos) 
{
   if (m_individual_property_screen.getActive())
   {
      return m_individual_property_screen.mouseDown(mouse_pos);
   }

   Screen::mouseDown(mouse_pos);
}

void PropertyScreen::mouseUp(sf::Vector2i mouse_pos) 
{
   if (m_individual_property_screen.getActive())
   {
      return m_individual_property_screen.mouseUp(mouse_pos);
   }

   Screen::mouseUp(mouse_pos);
}

void PropertyScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
   if (not m_active) return;
   
   if (m_individual_property_screen.getActive())
   {
      target.draw(m_individual_property_screen);
      return;
   }

   Screen::draw(target, states);

}

void PropertyScreen::handleClick(int button_id)
{
   switch(button_id)
   {
      case INDIVIDUAL:
         m_individual_property_screen.setActive(true);
      default: break;
   }
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
   m_individual_property_screen.setActive(false);
}


} // namespace Game