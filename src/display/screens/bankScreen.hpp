#pragma once
#include "screen.hpp"
#include "display/observableData.hpp"
#include "display/buttons/circleButton.hpp"

/*

This screen is for constructing a new loan. Choose
repayment plan and loan size here.

*/

namespace Game
{

class LoanScreen;

class BankScreen : public Screen
{
public:
   BankScreen(Ui& ui, LoanScreen& loan_screen, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
   void handleClick(int button_id) override;
   enum ButtonId {
      NONE = 0,
      LOAN
   };

   LoanScreen& m_loan_screen;
   CircleButton m_loan_button;
};

} // namespace Game