#pragma once
#include "screen.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/buttons/inputBoxNumberField.hpp"

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
   IndividualPropertyScreen(Ui& ui);
   void setSize(const sf::Vector2f& screen_size) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void dataSync() override;
   const Widget& getSubWidget(unsigned index) const override;
   Iterator end() const override { return Iterator(this, 7); }
private:
   CircleButton m_property_button;
   CircleButton m_manager_button;
   CircleButton m_save_button;
   CircleButton m_sell_button;
   CircleButton m_rent_button;

   bool m_managed;
   bool m_looking_for_tenants;
   bool m_rented;
   unsigned m_id;

   InputBoxNumberField m_price;
   InputBoxNumberField m_rental_price;
   sf::Text m_age;
   sf::Text m_rental_status;

   bool m_data_synced;
};

} // namespace Game