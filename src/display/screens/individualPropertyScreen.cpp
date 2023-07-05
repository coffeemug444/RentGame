#include "individualPropertyScreen.hpp"
#include "display/ui.hpp"
#include "propertyScreen.hpp"
#include "display/constColors.hpp"

namespace Game
{

IndividualPropertyScreen::IndividualPropertyScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Property 2",CC::individual_property_color)
,m_property_button(PROPERTY)
{
   m_property_button.setFillColor(CC::property_color);
   m_property_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);

   m_price.setFont(OD::font);
   m_price.setCharacterSize(15);
   m_price.setString("Price: ");
   m_age.setFont(OD::font);
   m_age.setCharacterSize(15);
   m_age.setString("Age: ");
}

std::vector<const Button*> IndividualPropertyScreen::getButtons() const
{
   return {&m_property_button};
}

void IndividualPropertyScreen::dataSync() 
{
   auto property = findById(OD::monitored_property_id, OD::Player::properties);
   if (not property.has_value()) return;
   std::string age_string = "Age: ";
   switch (property.value()->getAgeClass())
   {
   case Property::AgeClass::NEW:
      age_string += "NEW"; break;
   case Property::AgeClass::MID:
      age_string += "MID"; break;
   case Property::AgeClass::OLD:
      age_string += "OLD"; break;
   case Property::AgeClass::VERYOLD:
   default:
      age_string += "VERY OLD"; break;      
   }
   m_age.setString(age_string);
   m_price.setString(std::string("Price: ") + property.value()->getPrice());
}

void IndividualPropertyScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_property_button.setPosition({screen_size.x-2*m_property_button.getRadius(),0});
   m_age.setPosition({10,40});
   m_price.setPosition({10,60});
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
   target.draw(m_age);
   target.draw(m_price);
}



} // namespace Game