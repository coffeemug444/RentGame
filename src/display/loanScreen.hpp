#pragma once
#include "screen.hpp"

namespace Game
{

class LoanScreen : public Screen
{
public:
   LoanScreen(Ui& ui, sf::Vector2u screen_size) : Screen(ui, screen_size, sf::Color(0xe3c23dff)) {}
   virtual sf::Cursor::Type getCursorType(sf::Vector2u mouse_pos) const override { return sf::Cursor::Type::Arrow; }
};

} // namespace Game