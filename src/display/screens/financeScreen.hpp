#pragma once
#include "screen.hpp"

/*

This screen shows a line graph of:
 * net income
      - rent outgoing
      - loan repayment
      + rent incoming
 + capital
 - loan amount

this graph will extend a short while into the past, and make
a prediction lasting a short distance into the future. This does
not take into account random events.

*/

namespace Game
{

class FinanceScreen : public Screen
{
public:
   FinanceScreen(Ui& ui, sf::Vector2u screen_size);
   void handleClick(int button_id) override {}
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   std::vector<const Button*> getButtons() const override { return {}; }
};



} // namespace game
