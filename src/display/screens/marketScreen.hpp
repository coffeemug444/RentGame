#pragma once
#include "screen.hpp"
#include "display/constColors.hpp"

/*

This screen displays a list of all owned properties, with links
to manage each one 

*/

namespace Game
{

class MarketScreen : public Screen
{
public:
   MarketScreen(Ui& ui, sf::Vector2u screen_size) : Screen(ui, screen_size, "Market", CC::market_color) {}
   void handleClick(int button_id) override {}
};

} // namespace Game