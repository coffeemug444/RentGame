#pragma once

namespace Game
{

enum evTakeLoanStatus
{
   SUCCESS,
   FAILED
};

struct evTakeLoan
{
   int principal;
   int repayment_time_months;
   float interest_rate_yearly;
};

struct evLoanMonthlyPayment
{
   unsigned loan_id;
   int amount;
};

struct evNone {};

   
} // namespace Game
