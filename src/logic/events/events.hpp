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

struct evUpdatePropertyPrices
{
   unsigned property_id;
   int sale_price;
   int rental_price;
};

struct evNone {};

struct evPropertyManagedStatus
{
   unsigned property_id;
   bool managed;
};

struct evPropertyLookingForTenantsStatus
{
   unsigned property_id;
   bool looking_for_tenants;
};

   
} // namespace Game
