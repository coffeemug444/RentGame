#pragma once
#include "screen.hpp"
#include "bankScreen.hpp"
#include "display/buttons/circleButton.hpp"

/*

This screen shows a list of all current loans. It shows the 
total amount owed and a link to the bank screen to take out 
another loan.

*/

namespace Game
{

class LoanScreen : public Screen
{
public:
   LoanScreen(Ui& ui, sf::Vector2u screen_size);
   sf::Cursor::Type getCursorType(sf::Vector2i mouse_pos) const override;
   void mouseDown(sf::Vector2i mouse_pos) override;
   void mouseUp(sf::Vector2i mouse_pos) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void setScreenSize(sf::Vector2u screen_size) override;
   void setActive(bool active) override;
private:
   enum ButtonId {
      NONE = 0,
      BANK
   };

   void handleClick(int button_id) override;

   CircleButton m_bank_screen_button;
   BankScreen m_bank_screen;
};

} // namespace Game