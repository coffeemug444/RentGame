#include "loan.hpp"
#include <cmath>
#include "events/eventInterface.hpp"
#include <iostream>

   // int m_principle;
   // float m_interest_rate_monthly;
   // int m_loan_amount;
   // int m_payments_remaining;
   // int m_repayment_amount_monthly;

namespace Game
{


Loan::Loan(int principle, float interest_rate_monthly, int repayment_in_months, unsigned id)
:m_loan_id(id)
,m_principle(principle)
,m_interest_rate_monthly(interest_rate_monthly)
,m_loan_amount(principle)
,m_payments_remaining(repayment_in_months)
,m_day_count(0)
,m_accrued_interest_this_month(0)
,m_in_arrears(0)
{
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
   m_accrued_interest_this_month += (m_interest_rate_monthly/30.f) * m_loan_amount;
   m_day_count++;
   if (m_day_count < 30) return;
   m_day_count = 0;
   m_loan_amount += m_accrued_interest_this_month;
   m_accrued_interest_this_month = 0;
   recalculate_repayment_time();

   // send event telling game to pay monthly amount
   if (m_in_arrears)
   {
      EI::ev_loan_monthly_payment.push({m_loan_id, 2*m_repayment_amount_monthly});
   }
   else
   {
      EI::ev_loan_monthly_payment.push({m_loan_id, m_repayment_amount_monthly});
   }
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
   m_loan_amount -= amount;
   if (isInArrears() and amount == 2*m_repayment_amount_monthly)
   {
      m_in_arrears = false;
   }
}

} // namespace Game
