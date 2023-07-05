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

struct evPurchaseProperty
{
   unsigned listing_id;
};

struct evNone {};

struct evPropertyManagedStatus
{
   unsigned property_id;
   bool managed;
};

   
} // namespace Game
