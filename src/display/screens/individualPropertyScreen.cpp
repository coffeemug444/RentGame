#include "individualPropertyScreen.hpp"
#include "display/ui.hpp"
#include "propertyScreen.hpp"
#include "display/constColors.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{

IndividualPropertyScreen::IndividualPropertyScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Property 2",CC::individual_property_color)
,m_property_button(PROPERTY)
,m_manager_button(MANAGER)
,m_managed(false)
,m_id(0)
{
   m_property_button.setFillColor(CC::property_color);
   m_property_button.setRadius(0.05f*screen_size.y);

   m_price.setFont(OD::font);
   m_price.setCharacterSize(15);
   m_price.setString("Price: ");

   m_rental_price.setFont(OD::font);
   m_rental_price.setCharacterSize(15);
   m_rental_price.setString("Rental price: ");

   m_age.setFont(OD::font);
   m_age.setCharacterSize(15);
   m_age.setString("Age: ");

   m_rental_status.setFont(OD::font);
   m_rental_status.setCharacterSize(15);
   m_rental_status.setString("Rental status: ");

   m_manager_button.setFillColor(sf::Color::Red);
   m_manager_button.setRadius(0.05f*screen_size.y);

   setScreenSize(screen_size);
}

std::vector<const Button*> IndividualPropertyScreen::getButtons() const
{
   return {&m_property_button, &m_manager_button};
}

void IndividualPropertyScreen::dataSync() 
{
   m_id = OD::monitored_property_id;
   if (not listContainsId(m_id, OD::Player::properties)) return;
   const auto& property = *findById(m_id, OD::Player::properties).value();

   std::string age_string = "Age: ";
   switch (property.getAgeClass())
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
   m_price.setString(std::string("Price: ") + property.getPrice());
   m_rental_price.setString(std::string("Rental price: ") + property.getRentalPrice());

   if (property.isRented())
      m_rental_status.setString("Rental status: Rented");
   else if(property.lookingForRenters())
      m_rental_status.setString("Rental status: Looking for tenants");
   else
      m_rental_status.setString("Rental status: No tenants, not looking");

   m_managed = property.isManaged();

   if (m_managed)
      m_manager_button.setFillColor(sf::Color::Red);
   else
      m_manager_button.setFillColor(sf::Color::Green);
}

void IndividualPropertyScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_property_button.setPosition({screen_size.x-2*m_property_button.getRadius(),0});
   m_age.setPosition({10,40});
   m_price.setPosition({10,60});
   m_rental_price.setPosition({10,80});
   m_rental_status.setPosition({10,100});
   m_manager_button.setPosition({10,130});
}

void IndividualPropertyScreen::handleClick(int button_id) 
{
   switch (button_id)
   {
   case PROPERTY:
      m_ui.selectScreen(Ui::PROPERTIES);
      break;
   case MANAGER:
      {std::lock_guard lock(EI::gametick_mutex);
      EI::ev_set_property_managed_status.push({m_id, not m_managed});}
      break;
   default: break;
   }
}

void IndividualPropertyScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   Screen::draw(target, states);
   target.draw(m_age);
   target.draw(m_price);
   target.draw(m_rental_price);
   target.draw(m_rental_status);
   target.draw(m_manager_button);
}



} // namespace Game