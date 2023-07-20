#include "bankScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{

BankScreen::BankScreen() 
:Screen("Bank", CC::bank_color)
,m_title_container(this, {10,11}, COL)
,m_loan_screen_button([&](){EI::ev_switch_screen.push(Ui::LOANS);}, {V_CENTER,RIGHT})
,m_loan_amount_container(this, {4,5,6}, COL)
,m_loan_amount_label("Loan principal")
,m_loan_amount_field(CC::light_grey, sf::Color::Black, sf::Color::White, 10)
,m_loan_amount_errors()
,m_repayment_time_container(this, {7,8,9}, COL)
,m_repayment_time_label("Repayment time (months)")
,m_repayment_time_field(CC::light_grey, sf::Color::Black, sf::Color::White, 4)
,m_repayment_time_errors()
,m_take_loan_button([&](){handleTakeLoan();})
{
   m_loan_screen_button.setFillColor(CC::loan_color);
   m_title_container.setPadding({20,0,0,0});

   m_take_loan_button.setFillColor(CC::loan_color);

   m_loan_amount_errors.setFillColor(sf::Color::Red);
   m_repayment_time_errors.setFillColor(sf::Color::Red);
}

void BankScreen::setSubWidgetSize()
{
   auto inner_container_size = m_container_size - m_padding;
   float w = inner_container_size.x;
   float title_height = 60.f;
   m_title_container.setSize({w, title_height});
   float fields_height = 20.f;
   m_loan_amount_container.setSize({w, fields_height});
   m_repayment_time_container.setSize({w, fields_height});

   m_take_loan_button.setSize({w, 50.f}); // idk is this good???
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
   case 0:  return m_title_container;
   case 1:  return m_loan_amount_container;
   case 2:  return m_repayment_time_container;
   case 3:  return m_take_loan_button;
   case 4:  return m_loan_amount_label;
   case 5:  return m_loan_amount_field;
   case 6:  return m_loan_amount_errors;
   case 7:  return m_repayment_time_label;
   case 8:  return m_repayment_time_field;
   case 9:  return m_repayment_time_errors;
   case 10: return m_title;
   case 11: return m_loan_screen_button;
   default: return Widget::getSubWidget(index);
   }
}

void BankScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   Screen::draw(target, states);
   target.draw(m_loan_amount_errors);
   target.draw(m_repayment_time_errors);
}

} // namespace Game