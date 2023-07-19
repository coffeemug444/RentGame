#include "loanWidget.hpp"
#include "observableData.hpp"
#include "util/util.hpp"
#include "display/constColors.hpp"

namespace Game
{

LoanWidget::LoanWidget(unsigned id) : m_id(id) 
{
   const int CHAR_SIZE = 15;
   m_principal.setFont(OD::font);
   m_principal.setString("Principal: ");
   m_principal.setCharacterSize(CHAR_SIZE);
   m_total.setFont(OD::font);
   m_total.setString("Remaining: ");
   m_total.setCharacterSize(CHAR_SIZE);
   m_next_payment.setFont(OD::font);
   m_next_payment.setString("Next payment: ");
   m_next_payment.setCharacterSize(CHAR_SIZE);

   m_background_box.setFillColor(CC::light_grey);
   m_background_box.setSize({180.f, 3.f*CHAR_SIZE});
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
   // TODO: MAKE ALL THESE FIELDS INTO WIDGETS
   auto pos = getPosition();
   m_principal.setPosition(pos);
   m_total.setPosition(pos);
   m_next_payment.setPosition(pos);

   float y = size.y;
   float dy = y * 0.03f;
   m_principal.move({5,5});
   m_total.move({5,5+dy});
   m_next_payment.move({5,5+2*dy});

   float text_height = m_total.getGlobalBounds().height;

   auto box_size = m_background_box.getSize();
   m_background_box.setSize({box_size.x, text_height*2+2.f*dy});
}

void LoanWidget::move(const sf::Vector2f& pos)
{
   m_background_box.move(pos);
   m_principal.move(pos);
   m_total.move(pos);
   m_next_payment.move(pos);
}

void LoanWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_background_box);
   target.draw(m_principal);
   target.draw(m_total);
   target.draw(m_next_payment);
}


} // namespace Game
