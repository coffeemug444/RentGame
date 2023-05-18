#pragma once
#include "screen.hpp"
#include "observableData.hpp"

/*

This screen displays a single property with ways of managing
it like paying for maintenance, raising rent, hiring a property
manager etc.

*/

namespace Game
{

class IndividualPropertyScreen : public Screen
{
public:
   IndividualPropertyScreen(Ui& ui, sf::Vector2u screen_size) : Screen(ui, screen_size, "Property 2", sf::Color(OD::property_color)) {}
   virtual sf::Cursor::Type getCursorType(sf::Vector2u mouse_pos) const override { return sf::Cursor::Type::Arrow; }
};

} // namespace Game