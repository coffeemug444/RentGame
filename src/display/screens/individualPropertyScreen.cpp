#include "individualPropertyScreen.hpp"
#include "display/ui.hpp"
#include "propertyScreen.hpp"
#include "display/constColors.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{

IndividualPropertyScreen::IndividualPropertyScreen() 
:Screen("Property 2",CC::individual_property_color)
,m_title_container(this, {7, 8}, COL)
,m_property_button([&](){EI::ev_switch_screen.push(Ui::PROPERTIES);})
,m_age("Age: ")
,m_rental_status_container(this, {9,10}, COL)
,m_rental_status("Rental status: ")
,m_rent_button([&](){
      if (m_rented)
         EI::ev_evict_tenants_from_property_id.push(m_id);
      else
         EI::ev_set_property_looking_for_tenants_status.push({m_id, not m_looking_for_tenants});
   })
,m_rental_price_container(this, {11}, COL)
,m_rental_price(CC::light_grey, sf::Color::Black, sf::Color::White, 12, 10)
,m_sale_price_container(this, {12,13}, COL)
,m_price(CC::light_grey, sf::Color::Black, sf::Color::White, 12, 10)
,m_sell_button([&](){})
,m_save_prices_container(this, {14,15}, COL)
,m_save_prices_text("Save prices")
,m_save_button([&](){EI::ev_update_property_prices.push({m_id, m_price.getNumber(), m_rental_price.getNumber()});})
,m_manager_container(this, {16,17}, COL)
,m_managed_text("Managed by property manager: ")
,m_manager_button([&](){EI::ev_set_property_managed_status.push({m_id, not m_managed});})
,m_managed(false)
,m_looking_for_tenants(false)
,m_rented(false)
,m_id(0)
,m_data_synced(false)
{
   m_property_button.setFillColor(CC::property_color);

   m_save_button.setFillColor(sf::Color::Green);

   m_sell_button.setFillColor(sf::Color::Green);
   m_rent_button.setFillColor(sf::Color::Green);

   m_manager_button.setFillColor(sf::Color::Red);
}

void IndividualPropertyScreen::dataSync() 
{
   m_id = OD::monitored_property_id;
   if (not listContainsId(m_id, OD::Player::properties)) return;
   const auto& property = findById(m_id, OD::Player::properties).value().get();

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
   m_manager_button.setFillColor(m_managed ? sf::Color::Green : sf::Color::Red);
   m_managed_text.setString(std::string("Managed by property manager: ") + (m_managed ? "Yes" : "No"));

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
   case 0:  return m_title_container;
   case 1:  return m_age;
   case 2:  return m_rental_status_container;
   case 3:  return m_rental_price_container;
   case 4:  return m_sale_price_container;
   case 5:  return m_save_prices_container;
   case 6:  return m_manager_container;

   // held in sub-containers:
   case 7:  return m_title;
   case 8:  return m_property_button;

   case 9:  return m_rental_status;
   case 10: return m_rent_button;

   case 11: return m_rental_price;

   case 12: return m_price;
   case 13: return m_sell_button;

   case 14: return m_save_prices_text;
   case 15: return m_save_button;

   case 16: return m_managed_text;
   case 17: return m_manager_button;
   default: return Widget::getSubWidget(index);
   }
}




} // namespace Game