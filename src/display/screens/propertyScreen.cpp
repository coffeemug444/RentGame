#include "propertyScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"


namespace Game
{

PropertyScreen::PropertyScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Property", CC::property_color)
,m_individual_property_screen_button(INDIVIDUAL)
{
   m_individual_property_screen_button.setFillColor(CC::individual_property_color);
   m_individual_property_screen_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);
}

std::vector<const Button*> PropertyScreen::getButtons() const
{
   return {&m_individual_property_screen_button};
}

void PropertyScreen::handleClick(int button_id)
{
   switch(button_id)
   {
      case INDIVIDUAL:
         m_ui.selectScreen(Ui::INDIVIDUAL_PROPERTY);
      default: break;
   }
}

void PropertyScreen::setScreenSize(sf::Vector2u screen_size) 
{
   Screen::setScreenSize(screen_size);
   m_individual_property_screen_button.setPosition({screen_size.x-2*m_individual_property_screen_button.getRadius(),0});
}

} // namespace Game