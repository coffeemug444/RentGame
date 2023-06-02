#pragma once

namespace Game
{

class Loan
{
public:
   Loan(int principle, float interest_rate_monthly, int repayment_in_months);
   void pay(int amount);
   void advanceDay();

   void goIntoArrears() { m_in_arrears = true; }

   bool isInArrears() const { return m_in_arrears; }
   int getId() const { return m_loan_id; }
private:
   void recalculate_repayment_time();
   int m_loan_id;
   int m_principle;
   float m_interest_rate_monthly;
   int m_loan_amount;
   int m_payments_remaining;
   int m_repayment_amount_monthly;
   int m_day_count;
   int m_accrued_interest_this_moth;
   bool m_in_arrears; 
};



} // namespace Game
