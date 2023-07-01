#pragma once

namespace Game
{

class Loan
{
public:
   Loan(int principle, float interest_rate_monthly, int repayment_in_months, unsigned id);
   void pay(int amount);
   void advanceDay();

   void goIntoArrears() { m_in_arrears = true; }

   bool isInArrears() const { return m_in_arrears; }
   unsigned getId() const { return m_loan_id; }
   int getPrincipal() const { return m_principle; }
   int getRepaymentAmount() const { return m_repayment_amount_monthly; }
   int getAmount() const { return m_loan_amount; }
private:
   void recalculate_repayment_time();
   unsigned m_loan_id;
   int m_principle;
   float m_interest_rate_monthly;
   int m_loan_amount;
   int m_payments_remaining;
   int m_repayment_amount_monthly;
   int m_day_count;
   int m_accrued_interest_this_month;
   bool m_in_arrears; 
};



} // namespace Game
