#include "loan.hpp"
#include <cmath>
#include "events/eventInterface.hpp"
#include <iostream>
#include "observableData.hpp"
#include "util/util.hpp"

   // int m_principle;
   // float m_interest_rate_monthly;
   // int m_loan_amount;
   // int m_payments_remaining;
   // int m_repayment_amount_monthly;

namespace Game
{


Loan::Loan(int principle, float interest_rate_monthly, int repayment_in_months)
:m_loan_id(m_next_loan_id)
,m_principle(principle)
,m_interest_rate_monthly(interest_rate_monthly)
,m_loan_amount(principle)
,m_payments_remaining(repayment_in_months)
,m_repayment_day(OD::Date::getDayOfMonth())
,m_accrued_interest(0)
,m_in_arrears(0)
{
   m_next_loan_id++;
   double P = principle;
   double r = interest_rate_monthly;
   double n = repayment_in_months;
   
   m_repayment_amount_monthly = P * (r * std::pow(1 + r,n)) / (std::pow(1 + r,n) - 1);
}


void Loan::recalculate_repayment_time()
{
   double P = m_principle;
   double r = m_interest_rate_monthly;
   double A = m_repayment_amount_monthly;

   m_payments_remaining = ceil(-std::log(1 - (r * P) / A) / std::log(1 + r)) + 1;
}

void Loan::advanceDay()
{
   m_accrued_interest += (m_interest_rate_monthly/OD::Date::MONTH_LEN) * m_loan_amount;
   if (OD::Date::getDayOfMonth() != m_repayment_day) return;
   recalculate_repayment_time();

   int amount = m_repayment_amount_monthly;
   if (m_in_arrears) amount *= 2;

   if (OD::Player::capital < amount)
   {
      if (m_in_arrears)
      {
         // uh oh
         std::lock_guard lock(EI::gametick_mutex);
         EI::ev_stop_game.push({});
      }
      else goIntoArrears();
   }
   else
   {
      int to_pay = std::min(m_loan_amount + m_accrued_interest, amount);
      pay(to_pay);
      if (m_loan_amount == 0) deleteById(m_loan_id, OD::Player::loans);
   }
}

void Loan::goIntoArrears() 
{ 
   m_in_arrears = true; 
   m_loan_amount += m_accrued_interest;
   m_accrued_interest = 0;
}


/*
   pay off a portion of the debt early instead of at the end of the month. This
   will not affect the amount you have to pay at the end of each month.

   must pay             must pay    pay early  must pay               must pay 
   |                      |          |           |                      |
   v                      v          v           v                      v
   | New month            | New month            | New month            |

*/
void Loan::pay(int amount)
{
   if (OD::Player::capital < amount) return;
   OD::Player::capital -= amount;

   m_accrued_interest -= amount;
   if (m_accrued_interest >= 0) return;

   m_loan_amount += m_accrued_interest;
   m_accrued_interest = 0;
   if (isInArrears())   // if we're in arrears then one-off payments aren't allowed
   {
      m_in_arrears = false;
   }
}

} // namespace Game
