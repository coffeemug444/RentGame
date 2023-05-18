#pragma once
#include "screen.hpp"
#include "observableData.hpp"
#include "individualPropertyScreen.hpp"
#include "button.hpp"

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
   sf::Cursor::Type getCursorType(sf::Vector2i mouse_pos) const override;
   void mouseDown(sf::Vector2i mouse_pos) override;
   void mouseUp(sf::Vector2i mouse_pos) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void setScreenSize(sf::Vector2u screen_size) override;
   void setActive(bool active) override;
private:
   void individualPropertyScreenButtonCallback();

   bool m_individual_property_screen_open;
   Button<PropertyScreen> m_individual_property_screen_button;
   IndividualPropertyScreen m_individual_property_screen;
};

} // namespace Game