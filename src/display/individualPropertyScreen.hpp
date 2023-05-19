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
   IndividualPropertyScreen(Ui& ui, sf::Vector2u screen_size) : Screen(ui, screen_size, "Property 2", OD::individual_property_color) {}
};

} // namespace Game