#include "individualPropertyScreen.hpp"
#include "display/ui.hpp"
#include "propertyScreen.hpp"
#include "display/constColors.hpp"

namespace Game
{

IndividualPropertyScreen::IndividualPropertyScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Property 2",CC::individual_property_color,{&m_property_button})
,m_property_button(*this, PROPERTY)
{
   m_property_button.setFillColor(CC::property_color);
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
      m_ui.selectScreen(Ui::PROPERTIES);
      break;
   default: break;
   }
}

void IndividualPropertyScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   Screen::draw(target, states);
}



} // namespace Game