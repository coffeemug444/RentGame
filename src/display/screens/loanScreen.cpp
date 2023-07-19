#include "loanScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"
#include <algorithm>
#include "logic/events/eventInterface.hpp"

namespace Game
{

LoanScreen::LoanScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Loans", CC::loan_color) 
,m_bank_screen_button([&](){EI::ev_switch_screen.push(Ui::BANK);})
{
   m_bank_screen_button.setFillColor(CC::bank_color);
   m_bank_screen_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);
}

void LoanScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_bank_screen_button.setPosition({screen_size.x-2*m_bank_screen_button.getRadius(),0});
   sf::Vector2f loan_widget_origin = {10.f,0.1f*screen_size.y};
   for (int i = 0; i < m_loan_widgets.size(); i++)
   {
      auto new_pos = loan_widget_origin + i*sf::Vector2f{0,20.f+m_loan_widgets[i]->getSize().y};
      m_loan_widgets[i]->setPosition(new_pos);
   }
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
   if (changed) setScreenSize(m_screen_size);

   Screen::dataSync();
}

} // namespace Game