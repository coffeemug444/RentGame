#pragma once
#include "screen.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/widgets/loanWidget.hpp"
#include <memory>

#include <iostream>

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
   LoanScreen();
   void setSize(const sf::Vector2f& size) override;
   void dataSync() override;
   const Widget& getSubWidget(unsigned index) const override;
   Iterator end() const override { return Iterator(this, 1 + m_loan_widgets.size()); }
private:

   CircleButton m_bank_screen_button;
   std::vector<std::shared_ptr<LoanWidget>> m_loan_widgets;
};

} // namespace Game