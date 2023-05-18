#pragma once
#include "screen.hpp"
#include "observableData.hpp"

/*

This screen displays a list of all owned properties, with links
to manage each one 

*/

namespace Game
{

class PropertyScreen : public Screen
{
public:
   PropertyScreen(Ui& ui, sf::Vector2u screen_size) : Screen(ui, screen_size, "Property", sf::Color(OD::property_color)) {}
   virtual sf::Cursor::Type getCursorType(sf::Vector2i mouse_pos) const override { return sf::Cursor::Type::Arrow; }
};

} // namespace Game