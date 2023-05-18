#pragma once
#include "screen.hpp"
#include "observableData.hpp"

/*

This screen is for constructing a new loan. Choose
repayment plan and loan size here.

*/

namespace Game
{

class BankScreen : public Screen
{
public:
   BankScreen(Ui& ui, sf::Vector2u screen_size) : Screen(ui, screen_size, "Bank", sf::Color(OD::bank_color)) {}
   virtual sf::Cursor::Type getCursorType(sf::Vector2u mouse_pos) const override { return sf::Cursor::Type::Arrow; }
};

} // namespace Game