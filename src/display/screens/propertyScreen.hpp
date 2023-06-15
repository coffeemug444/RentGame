#pragma once
#include "screen.hpp"
#include "display/buttons/circleButton.hpp"

/*

This screen displays a list of all owned properties, with links
to manage each one 

*/

namespace Game
{

class PropertyScreen : public Screen
{
public:
   PropertyScreen(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size) override;
private:
   enum ButtonId {
      NONE = 0,
      INDIVIDUAL
   };
   void handleClick(int button_id) override;

   CircleButton m_individual_property_screen_button;
};

} // namespace Game