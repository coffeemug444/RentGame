#include "bankScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{

BankScreen::BankScreen() 
:Screen("Bank", CC::bank_color)
,m_loan_screen_button([&](){EI::ev_switch_screen.push(Ui::LOANS);})
,m_loan_amount_field("Loan total", CC::light_grey, sf::Color::Black, sf::Color::White, 12, 10)
,m_repayment_time_field("Repayment time (months)", CC::light_grey, sf::Color::Black, sf::Color::White, 12, 4)
,m_take_loan_button([&](){handleTakeLoan();})
{
   m_loan_screen_button.setFillColor(CC::loan_color);
   m_take_loan_button.setFillColor(CC::loan_color);

   m_loan_amount_errors.setFont(OD::font);
   m_loan_amount_errors.setCharacterSize(12);
   m_loan_amount_errors.setFillColor(sf::Color::Red);
   m_repayment_time_errors.setFont(OD::font);
   m_repayment_time_errors.setCharacterSize(12);
   m_repayment_time_errors.setFillColor(sf::Color::Red);


}

void BankScreen::setSize(const sf::Vector2f& screen_size)
{
   Screen::setSize(screen_size);
   m_loan_screen_button.setRadius(0.05f*screen_size.y);
   m_take_loan_button.setRadius(0.05f*screen_size.y);
   m_loan_screen_button.setPosition({screen_size.x-2*m_loan_screen_button.getRadius(),0});
   m_loan_amount_field.setPosition({0,0.1f*screen_size.y});
   m_repayment_time_field.setPosition({0,0.15f*screen_size.y});
   m_take_loan_button.setPosition({0,0.2f*screen_size.y + m_loan_screen_button.getRadius()});
   m_loan_amount_errors.setPosition({m_loan_amount_field.getSize().x,0.1f*screen_size.y});
   m_repayment_time_errors.setPosition({m_repayment_time_field.getSize().x,0.15f*screen_size.y});
}

void BankScreen::handleTakeLoan()
{
   int amount = m_loan_amount_field.getNumber();
   int repayment_time = m_repayment_time_field.getNumber();
   float interest_rate = 0.045;
   
   bool errors = setErrors(amount, repayment_time, interest_rate);
   if (errors) return;
   
   EI::ev_take_loan.push({amount, repayment_time, interest_rate});
   m_loan_amount_field.reset();
   m_repayment_time_field.reset();
}

bool BankScreen::setErrors(int amount, int repayment_time, float interest_rate)
{
   resetErrors();

   bool errors = false;
   if (amount == 0)
   {
      errors = true;
      m_loan_amount_errors.setString("Amount cannot be 0");
   }
   if (repayment_time == 0)
   {
      errors = true;
      m_repayment_time_errors.setString("Repayment time must be at least 1 month");
   }

   return errors;
}

void BankScreen::resetErrors()
{
   m_loan_amount_errors.setString("");
   m_repayment_time_errors.setString("");
}

// TODO: THIS DOESN'T LOOK RIGHT
void BankScreen::uiEvents()
{
   Screen::uiEvents();
   if (EI::ev_take_loan_status.size() > 0)
   {
      std::lock_guard lock(EI::gametick_mutex);
      while (EI::ev_take_loan_status.size() > 0)
      {
         auto status = EI::ev_take_loan_status.front();
         switch (status)
         {
         case SUCCESS:
            EI::ev_switch_screen.push(Ui::LOANS);
            break;
         case FAILED:
            break;
         }
         EI::ev_take_loan_status.pop(); // ??? shouldn't this be in gameLogic?
      }
   }
}


const Widget& BankScreen::getSubWidget(unsigned index) const
{
   switch (index)
   {
   case 0: return m_loan_amount_field;
   case 1: return m_repayment_time_field;
   case 2: return m_loan_screen_button;
   case 3: return m_take_loan_button;
   default: return Widget::getSubWidget(index);
   }
}

void BankScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   Screen::draw(target, states);
   target.draw(m_loan_amount_field);
   target.draw(m_repayment_time_field);
   target.draw(m_loan_amount_errors);
   target.draw(m_repayment_time_errors);
}

} // namespace Game