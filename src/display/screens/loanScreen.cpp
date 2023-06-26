#include "loanScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"
#include <algorithm>

namespace Game
{

LoanScreen::LoanScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Loans", CC::loan_color, {&m_bank_screen_button}) 
,m_bank_screen_button(*this, BANK)
{
   m_bank_screen_button.setFillColor(CC::bank_color);
   m_bank_screen_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);
}

void LoanScreen::handleClick(int button_id)
{
   switch(button_id)
   {
   case BANK:
      m_ui.selectScreen(Ui::BANK);
      break;
   default: break;
   }
}

std::vector<Widget*> LoanScreen::getSubWidgets()
{
   std::vector<Widget*> widgets(m_loan_widgets.size());
   std::transform(m_loan_widgets.begin(), m_loan_widgets.end(), widgets.begin(),
      [](LoanWidget& loan_widget) -> Widget* { return &loan_widget; }
   );
   return widgets;
}

std::vector<const Widget*> LoanScreen::getSubWidgets() const
{
   std::vector<const Widget*> widgets(m_loan_widgets.size());
   std::transform(m_loan_widgets.begin(), m_loan_widgets.end(), widgets.begin(),
      [](const LoanWidget& loan_widget) -> const Widget* { return &loan_widget; }
   );
   return widgets;
}

void LoanScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_bank_screen_button.setPosition({screen_size.x-2*m_bank_screen_button.getRadius(),0});
}

} // namespace Game