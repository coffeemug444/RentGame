#include "individualPropertyScreen.hpp"
#include "ui.hpp"
#include "propertyScreen.hpp"

namespace Game
{

IndividualPropertyScreen::IndividualPropertyScreen(Ui& ui, PropertyScreen& property_screen, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Property 2",OD::individual_property_color,{&m_property_button})
,m_property_screen(property_screen)
,m_property_button(*this, PROPERTY)
{
   m_property_button.setFillColor(OD::property_color);
   m_property_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);
}

void IndividualPropertyScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_property_button.setPosition({screen_size.x-2*m_property_button.getRadius(),0});
}

void IndividualPropertyScreen::handleClick(int button_id) 
{
   switch (button_id)
   {
   case PROPERTY:
      setActive(false);
      m_property_screen.setActive(true);
      break;
   default: break;
   }
}

void IndividualPropertyScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (not m_active) return;
   Screen::draw(target, states);

   target.draw(m_property_button);
}



} // namespace Game