#pragma once
#include "screen.hpp"
#include "observableData.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/buttons/inputBoxNumberField.hpp"

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
   BankScreen(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void charEntered(char c) override;
   void backspace() override;
   void uiEvents() override;
   std::vector<const Widget*> getSubWidgets() const override;
   std::vector<Widget*> getSubWidgets() override;
   std::vector<const Button*> getButtons() const override;
private:
   void handleClick(int button_id) override;
   void handleTakeLoan();

   // returns true if errors were set
   bool setErrors(int amount, int repayment_time, float interest_rate);
   void resetErrors();
   enum ButtonId {
      NONE = 0,
      LOAN_SCREEN,
      TAKE_LOAN
   };

   CircleButton m_loan_screen_button;

   InputBoxNumberField m_loan_amount_field;
   sf::Text m_loan_amount_errors;

   InputBoxNumberField m_repayment_time_field;
   sf::Text m_repayment_time_errors;

   CircleButton m_take_loan_button;

};

} // namespace Game