#pragma once
#include "screen.hpp"
#include "observableData.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/buttons/inputBoxNumberField.hpp"
#include "display/widgets/containerWidget.hpp"
#include "display/widgets/textWidget.hpp"

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
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void uiEvents() override;
   const Widget& getSubWidget(unsigned index) const override;
   void setSubWidgetSize() override;
   Iterator end() const override { return Iterator(this, 4); }
private:
   void handleTakeLoan();

   // returns true if errors were set
   bool setErrors(int amount, int repayment_time, float interest_rate);
   void resetErrors();

   ContainerWidget m_title_container;
   CircleButton m_loan_screen_button;

   ContainerWidget m_loan_amount_container;
   TextWidget m_loan_amount_label;
   InputBoxNumberField m_loan_amount_field;
   TextWidget m_loan_amount_errors;

   ContainerWidget m_repayment_time_container;
   TextWidget m_repayment_time_label;
   InputBoxNumberField m_repayment_time_field;
   TextWidget m_repayment_time_errors;

   CircleButton m_take_loan_button;

};

} // namespace Game