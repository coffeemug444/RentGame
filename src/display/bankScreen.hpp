#pragma once
#include "screen.hpp"
#include "observableData.hpp"

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
   BankScreen(Ui& ui, LoanScreen& loan_screen, sf::Vector2u screen_size);
private:
   LoanScreen& m_loan_screen;
};

} // namespace Game