#include "bankScreen.hpp"
#include "ui.hpp"

namespace Game
{

BankScreen::BankScreen(Ui& ui, LoanScreen& loan_screen, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Bank", OD::bank_color, {&m_loan_button})
,m_loan_screen(loan_screen) 
,m_loan_button(*this, LOAN)
{
   m_loan_button.setFillColor(OD::loan_color);
   m_loan_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);
}

void BankScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_loan_button.setPosition({screen_size.x-2*m_loan_button.getRadius(),0});
}

void BankScreen::handleClick(int button_id) 
{
   switch (button_id)
   {
   case LOAN:
      setActive(false);
      m_loan_screen.setActive(true);
      break;
   default: break;
   }
}

void BankScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (not m_active) return;
   Screen::draw(target, states);

   target.draw(m_loan_button);
}

} // namespace Game