#include "loanWidget.hpp"
#include "observableData.hpp"
#include "util/util.hpp"

namespace Game
{

LoanWidget::LoanWidget(unsigned id) : m_id(id) 
{
   m_principal.setFont(OD::font);
   m_total.setFont(OD::font);
   m_next_payment.setFont(OD::font);
}


void LoanWidget::dataSync() 
{
   auto opt_loan = findById(m_id, OD::Player::loans);
   if (not opt_loan.has_value()) return;
   const Loan& loan = *opt_loan.value();

   //std::to_string()
   m_principal.setString(   std::to_string(loan.getPrincipal()));
   m_total.setString(       std::to_string(loan.getAmount()));
   m_next_payment.setString(std::to_string(loan.getRepaymentAmount()));
}

void LoanWidget::handleClick(int button_id)
{
   // no buttons yet
}


void LoanWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   std::cout << "drawing a loan widget" << std::endl;
   target.draw(m_principal);
   target.draw(m_total);
   target.draw(m_next_payment);
}


} // namespace Game
