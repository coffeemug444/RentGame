#pragma once
#include "screen.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/buttons/inputBoxNumberField.hpp"
#include "display/widgets/textWidget.hpp"
#include "display/widgets/containerWidget.hpp"

/*

This screen displays a single property with ways of managing
it like paying for maintenance, raising rent, hiring a property
manager etc.

*/

namespace Game
{

class PropertyScreen;

class IndividualPropertyScreen : public Screen
{
public:
   IndividualPropertyScreen();
   void dataSync() override;
   const Widget& getSubWidget(unsigned index) const override;
   Iterator end() const override { return Iterator(this, 7); }
private:
   ContainerWidget m_title_container;
   CircleButton m_property_button;

   TextWidget m_age;

   ContainerWidget m_rental_status_container;
   TextWidget m_rental_status;
   CircleButton m_rent_button;

   ContainerWidget m_rental_price_container;
   InputBoxNumberField m_rental_price;

   ContainerWidget m_sale_price_container;
   InputBoxNumberField m_price;
   CircleButton m_sell_button;

   ContainerWidget m_save_prices_container;
   TextWidget m_save_prices_text;
   CircleButton m_save_button;

   ContainerWidget m_manager_container;
   TextWidget m_managed_text;
   CircleButton m_manager_button;

   bool m_managed;
   bool m_looking_for_tenants;
   bool m_rented;
   unsigned m_id;


   bool m_data_synced;
};

} // namespace Game