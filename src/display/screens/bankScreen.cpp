#include "bankScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{

BankScreen::BankScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Bank", CC::bank_color, 
        {&m_loan_screen_button, &m_take_loan_button})
,m_loan_screen_button(*this, LOAN_SCREEN)
,m_loan_amount_field("Loan total", CC::light_grey, sf::Color::Black, sf::Color::White, 12, 10)
,m_repayment_time_field("Repayment time (months)", CC::light_grey, sf::Color::Black, sf::Color::White, 12, 4)
,m_take_loan_button(*this, TAKE_LOAN)
{
   m_loan_screen_button.setFillColor(CC::loan_color);
   m_take_loan_button.setFillColor(CC::loan_color);
   setScreenSize(screen_size);

   m_loan_amount_errors.setFont(OD::font);
   m_loan_amount_errors.setFillColor(sf::Color::Red);
   m_repayment_time_errors.setFont(OD::font);
   m_repayment_time_errors.setFillColor(sf::Color::Red);


}

void BankScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_loan_screen_button.setRadius(0.05f*screen_size.y);
   m_take_loan_button.setRadius(0.05f*screen_size.y);
   m_loan_screen_button.setPosition({screen_size.x-2*m_loan_screen_button.getRadius(),0});
   m_loan_amount_field.setPosition({0,0.1f*screen_size.y});
   m_repayment_time_field.setPosition({0,0.15f*screen_size.y});
   m_take_loan_button.setPosition({0,0.2f*screen_size.y + m_loan_screen_button.getRadius()});
}

void BankScreen::handleClick(int button_id) 
{
   switch (button_id)
   {
   case LOAN_SCREEN:
      m_ui.selectScreen(Ui::LOANS);
      break;
   case TAKE_LOAN:
      handleTakeLoan();
      break;
   default: break;
   }
}

void BankScreen::handleTakeLoan()
{
   EI::ev_take_loan.push({m_loan_amount_field.getNumber(), m_repayment_time_field.getNumber(), 0.045f});
   m_loan_amount_field.reset();
   m_repayment_time_field.reset();
}

void BankScreen::charEntered(char c) 
{
   if (c < '0' or c > '9') return;
   m_loan_amount_field.addDigit(c);
   m_repayment_time_field.addDigit(c);
}

void BankScreen::backspace() 
{
   m_loan_amount_field.backSpace();
   m_repayment_time_field.backSpace();
}

void BankScreen::uiEvents()
{
   Screen::uiEvents();
   while (EI::ev_take_loan_status.size() > 0)
   {
      auto status = EI::ev_take_loan_status.front();
      switch (status)
      {
      case SUCCESS:
         m_ui.selectScreen(Ui::LOANS);
         break;
      case FAILED:
         break;
      }
      EI::ev_take_loan_status.pop();
   }
}

std::vector<const Widget*> BankScreen::getSubWidgets() const
{
   return {&m_loan_amount_field, &m_repayment_time_field};
}

std::vector<Widget*> BankScreen::getSubWidgets()
{
   return {&m_loan_amount_field, &m_repayment_time_field};
}

void BankScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   Screen::draw(target, states);
   target.draw(m_loan_amount_field);
   target.draw(m_repayment_time_field);
}

} // namespace Game