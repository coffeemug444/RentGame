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

struct evNone {};

   
} // namespace Game
