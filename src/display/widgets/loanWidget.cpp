#include "loanWidget.hpp"
#include "observableData.hpp"
#include "util/util.hpp"
#include "display/constColors.hpp"

namespace Game
{

LoanWidget::LoanWidget(unsigned id) 
:m_id(id) 
,m_principal("Principal: ")
,m_total("Remaining: ")
,m_next_payment("Next payment: ")
{
   setPadding({20,20,20,20});
   m_background_box.setFillColor(CC::light_grey);
}


void LoanWidget::dataSync() 
{
   auto opt_loan = findById(m_id, OD::Player::loans);
   if (not opt_loan.has_value()) return;
   const Loan& loan = opt_loan.value().get();

   m_principal.setString(std::string("Principal: ") + loan.getPrincipal());
   m_total.setString(std::string("Remaining: ") + loan.getAmount());
   m_next_payment.setString(std::string("Next payment: ") + loan.getRepaymentAmount());
}

void LoanWidget::setSize(const sf::Vector2f& size)
{
   Widget::setSize(size);
   m_background_box.setSize(size - m_padding);
   m_background_box.setPosition(getPosition());
   m_background_box.move({m_padding.left, m_padding.top});
}

void LoanWidget::move(const sf::Vector2f& pos)
{
   Widget::move(pos);
   m_background_box.move(pos);
}

const Widget& LoanWidget::getSubWidget(unsigned index) const { 
   switch (index)
   {
   case 0: return m_principal;
   case 1: return m_total;
   case 2: return m_next_payment;
   default: return Widget::getSubWidget(index);
   }
}

void LoanWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_background_box);
   Widget::draw(target, states);
}


} // namespace Game
