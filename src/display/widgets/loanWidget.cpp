#include "loanWidget.hpp"
#include "observableData.hpp"
#include "util/util.hpp"

namespace Game
{

LoanWidget::LoanWidget(unsigned id) : m_id(id) 
{
   m_principal.setFont(OD::font);
   m_principal.setCharacterSize(15);
   m_total.setFont(OD::font);
   m_total.setCharacterSize(15);
   m_next_payment.setFont(OD::font);
   m_next_payment.setCharacterSize(15);
}


void LoanWidget::dataSync() 
{
   auto opt_loan = findById(m_id, OD::Player::loans);
   if (not opt_loan.has_value()) return;
   const Loan& loan = *opt_loan.value();

   m_principal.setString(std::string("Principal: ") + loan.getPrincipal());
   m_total.setString(std::string("Remaining: ") + loan.getAmount());
   m_next_payment.setString(std::string("Next payment: ") + loan.getRepaymentAmount());
}

void LoanWidget::handleClick(int button_id)
{
   // no buttons yet
}

sf::Vector2f LoanWidget::getSize() const
{
   auto l1 = m_principal.getLocalBounds();
   auto l2 = m_total.getLocalBounds();
   auto l3 = m_next_payment.getLocalBounds();

   float x = std::max(l1.width, std::max(l2.width,l3.width));
   float y = 0.09*m_screen_size.y;
   return {x,y};
}

sf::Vector2f LoanWidget::getPosition() const
{
   return m_principal.getPosition();
}

void LoanWidget::setScreenSize(const sf::Vector2u& size)
{
   m_screen_size = size;

   auto pos = getPosition();
   m_principal.setPosition(pos);
   m_total.setPosition(pos);
   m_next_payment.setPosition(pos);

   float y = size.y;
   float dy = y * 0.03f;
   m_total.move({0,dy});
   m_next_payment.move({0,2*dy});
}

void LoanWidget::move(const sf::Vector2f& pos)
{
   m_principal.move(pos);
   m_total.move(pos);
   m_next_payment.move(pos);
}

void LoanWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_principal);
   target.draw(m_total);
   target.draw(m_next_payment);
}


} // namespace Game
