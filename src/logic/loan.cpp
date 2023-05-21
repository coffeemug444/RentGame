#include "loan.hpp"
#include <cmath>

   // int m_principle;
   // float m_interest_rate_monthly;
   // int m_loan_amount;
   // int m_payments_remaining;
   // int m_repayment_amount_monthly;

namespace Game
{


Loan::Loan(int principle, float interest_rate_monthly, int repayment_in_months)
:m_principle(principle)
,m_interest_rate_monthly(interest_rate_monthly)
,m_loan_amount(principle)
,m_payments_remaining(repayment_in_months)
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

} // namespace Game
