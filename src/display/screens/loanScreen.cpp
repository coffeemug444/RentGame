#include "loanScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"
#include <algorithm>
#include "logic/events/eventInterface.hpp"

namespace Game
{

LoanScreen::LoanScreen() 
:Screen("Loans", CC::loan_color) 
,m_bank_screen_button([&](){EI::ev_switch_screen.push(Ui::BANK);})
{
   m_bank_screen_button.setFillColor(CC::bank_color);
}

void LoanScreen::setSize(const sf::Vector2f& size)
{
   Screen::setSize(size);

   // TODO: PUT EVERYTHING WHERE IT SHOULD BE (using containerWidgets??)
}


const Widget& LoanScreen::getSubWidget(unsigned index) const 
{ 
   if (index == 0) return m_bank_screen_button;
   return *(m_loan_widgets.at(index - 1)); 
}

void LoanScreen::dataSync() 
{
   bool changed = false;
   for (const auto& loan : OD::Player::loans)
   {
      if (not listContainsId(loan.getId(), m_loan_widgets))
      {
         m_loan_widgets.push_back(std::make_shared<LoanWidget>(loan.getId()));
         changed = true;
      }
   }
   for (int i = 0; i < m_loan_widgets.size(); i++)
   {
      if (not listContainsId(m_loan_widgets[i]->getId(), OD::Player::loans))
      {
         m_loan_widgets.erase(m_loan_widgets.begin() + i);
         i--;
         changed = true;
      }
   }
   if (changed) Widget::placeSubWidgets();

   Screen::dataSync();
}

} // namespace Game