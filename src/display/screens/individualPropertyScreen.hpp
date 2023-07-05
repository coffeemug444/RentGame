#pragma once
#include "screen.hpp"
#include "display/buttons/circleButton.hpp"

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
   IndividualPropertyScreen(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   std::vector<const Button*> getButtons() const override;
   void dataSync() override;
private:
   void handleClick(int button_id) override;
   enum ButtonId {
      NONE = 0,
      PROPERTY,
      MANAGER
   };
   CircleButton m_property_button;
   CircleButton m_manager_button;

   bool m_managed;
   unsigned m_id;

   sf::Text m_price;
   sf::Text m_age;
};

} // namespace Game