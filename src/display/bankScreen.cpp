#include "bankScreen.hpp"
#include "ui.hpp"

namespace Game
{

BankScreen::BankScreen(Ui& ui, LoanScreen& loan_screen, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Bank", sf::Color(OD::bank_color))
,m_loan_screen(loan_screen) 
{
}


} // namespace Game