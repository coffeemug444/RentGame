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
   BankScreen();
   void setSize(const sf::Vector2f& screen_size) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void uiEvents() override;
   const Widget& getSubWidget(unsigned index) const override;
   Iterator end() const override { return Iterator(this, 4); }
private:
   void handleTakeLoan();

   // returns true if errors were set
   bool setErrors(int amount, int repayment_time, float interest_rate);
   void resetErrors();

   CircleButton m_loan_screen_button;

   InputBoxNumberField m_loan_amount_field;
   sf::Text m_loan_amount_errors;

   InputBoxNumberField m_repayment_time_field;
   sf::Text m_repayment_time_errors;

   CircleButton m_take_loan_button;

};

} // namespace Game