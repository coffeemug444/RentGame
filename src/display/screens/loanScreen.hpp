#pragma once
#include "screen.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/widgets/loanWidget.hpp"

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
   LoanScreen(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size) override;
   void dataSync() override;
   std::vector<const Button*> getButtons() const override;
   const Widget& getSubWidget(unsigned index) const override { return m_loan_widgets.at(index); }
   Iterator end() const override { return Iterator(this, m_loan_widgets.size()); }
private:
   enum ButtonId {
      NONE = 0,
      BANK
   };

   void handleClick(int button_id) override;

   CircleButton m_bank_screen_button;
   std::vector<LoanWidget> m_loan_widgets;
};

} // namespace Game