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
,m_save_button(SAVE)
,m_sell_button(SELL)
,m_rent_button(RENT)
,m_managed(false)
,m_looking_for_tenants(false)
,m_rented(false)
,m_id(0)
,m_price("Price", CC::light_grey, sf::Color::Black, sf::Color::White, 12, 10)
,m_rental_price("Rental price", CC::light_grey, sf::Color::Black, sf::Color::White, 12, 10)
,m_data_synced(false)
{
   m_property_button.setFillColor(CC::property_color);
   m_property_button.setRadius(0.05f*screen_size.y);

   m_save_button.setFillColor(sf::Color::Green);
   m_save_button.setRadius(0.05f*screen_size.y);

   m_sell_button.setFillColor(sf::Color::Green);
   m_sell_button.setRadius(0.025f*screen_size.y);
   m_rent_button.setFillColor(sf::Color::Green);
   m_rent_button.setRadius(0.025f*screen_size.y);

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
   return {&m_property_button, &m_manager_button, &m_save_button, &m_sell_button, &m_rent_button};
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

   m_looking_for_tenants = property.getLookingForTenants();
   m_rented = property.isRented();

   if (m_rented)
   {
      m_rental_status.setString("Rental status: Rented");
      m_rent_button.setFillColor(sf::Color::Red);
   }
   else if(m_looking_for_tenants)
   {      
      m_rental_status.setString("Rental status: Looking for tenants");
      m_rent_button.setFillColor(sf::Color::Yellow);
   }
   else
   {
      m_rental_status.setString("Rental status: No tenants, not looking");
      m_rent_button.setFillColor(sf::Color::Green);
   }

   m_managed = property.isManaged();

   m_price.setEditable(not m_managed);
   m_rental_price.setEditable(not m_managed);
   m_manager_button.setFillColor(m_managed ? sf::Color::Red : sf::Color::Green);

   if (not m_data_synced or m_managed)
   {
      m_price.setNumber(property.getPrice());
      m_rental_price.setNumber(property.getRentalPrice());
   }

   m_data_synced = true;
}


const Widget& IndividualPropertyScreen::getSubWidget(unsigned index) const 
{
   switch (index)
   {
   case 0: return m_price;
   case 1: return m_rental_price;
   default: return Widget::getSubWidget(index);
   }
}

void IndividualPropertyScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_property_button.setPosition({screen_size.x-2*m_property_button.getRadius(),0});
   m_save_button.setPosition({300,60});
   m_age.setPosition({10,40});
   m_price.setPosition({10,60});
   m_rental_price.setPosition({10,80});
   m_rental_status.setPosition({10,100});
   m_manager_button.setPosition({10,130});
   m_sell_button.setPosition({300,130});
   m_rent_button.setPosition({350,130});
}

void IndividualPropertyScreen::handleClick(int button_id) 
{
   switch (button_id)
   {
   case PROPERTY:
      m_ui.selectScreen(Ui::PROPERTIES);
      m_data_synced = false;
      break;
   case MANAGER:
      {std::lock_guard lock(EI::gametick_mutex);
      EI::ev_set_property_managed_status.push({m_id, not m_managed});}
      break;
   case SAVE:
      {std::lock_guard lock(EI::gametick_mutex);
      EI::ev_update_property_prices.push({m_id, m_price.getNumber(), m_rental_price.getNumber()});}
      break;
   case SELL:
      break;
   case RENT:
      {std::lock_guard lock(EI::gametick_mutex);
      if (m_rented)
         EI::ev_evict_tenants_from_property_id.push(m_id);
      else
         EI::ev_set_property_looking_for_tenants_status.push({m_id, not m_looking_for_tenants});
      }
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
   target.draw(m_sell_button);
   target.draw(m_rent_button);
}



} // namespace Game