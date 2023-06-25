#include "bankScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"


namespace Game
{

BankScreen::BankScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Bank", CC::bank_color, 
        {&m_loan_screen_button, &m_take_loan_button}, 
        {&m_loan_amount_field, &m_repayment_time_field})
,m_loan_screen_button(*this, LOAN_SCREEN)
,m_loan_amount_field(CC::light_grey, sf::Color::Black, sf::Color::White, 12)
,m_repayment_time_field(CC::light_grey, sf::Color::Black, sf::Color::White, 12)
,m_take_loan_button(*this, TAKE_LOAN)
{
   m_loan_screen_button.setFillColor(CC::loan_color);
   m_loan_screen_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);

   m_loan_amount_errors.setFont(OD::font);
   m_loan_amount_errors.setFillColor(sf::Color::Red);
   m_repayment_time_errors.setFont(OD::font);
   m_repayment_time_errors.setFillColor(sf::Color::Red);


}

void BankScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_loan_screen_button.setPosition({screen_size.x-2*m_loan_screen_button.getRadius(),0});
   m_loan_amount_field.setPosition({0,0.1f*screen_size.y});
   m_repayment_time_field.setPosition({0,0.2f*screen_size.y});
}

void BankScreen::handleClick(int button_id) 
{
   switch (button_id)
   {
   case LOAN_SCREEN:
      m_ui.selectScreen(Ui::LOANS);
      break;
   default: break;
   }
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

void BankScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   Screen::draw(target, states);
   target.draw(m_loan_amount_field);
   target.draw(m_repayment_time_field);
}

} // namespace Game