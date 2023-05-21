#pragma once

namespace Game
{


class Loan
{
public:
   Loan(int principle, float interest_rate_monthly, int repayment_in_months);
private:
   void recalculate_repayment_time();
   int m_principle;
   float m_interest_rate_monthly;
   int m_loan_amount;
   int m_payments_remaining;
   int m_repayment_amount_monthly;
};



} // namespace Game
