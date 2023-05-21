#pragma once
#include "screen.hpp"
#include "display/observableData.hpp"

/*

This screen displays a list of all owned properties, with links
to manage each one 

*/

namespace Game
{

class MarketScreen : public Screen
{
public:
   MarketScreen(Ui& ui, sf::Vector2u screen_size) : Screen(ui, screen_size, "Market", OD::market_color) {}
};

} // namespace Game