#include "property.hpp"
#include "observableData.hpp"
#include "util/util.hpp"

namespace Game
{


Property::Property(int price, int age)
:m_id(m_next_property_id)
,m_price(price)
,m_age(age)
,m_rental_price(0)
,m_rented(false)
,m_rent_day(0)
,m_renter_dissatisfaction(0)
,m_managed(false)
,m_looking_for_tenants(false)
,m_to_be_sold(false)
{
   m_next_property_id++;
}

Property::AgeClass Property::getAgeClass(int age)
{
   // NOTE: may need adjusting
   if (age <= 2*OD::Date::YEAR_LEN) return NEW;
   if (age <= 5*OD::Date::YEAR_LEN) return MID;
   if (age <= 7*OD::Date::YEAR_LEN) return OLD;
   return VERYOLD;
}


float Property::getProblemChance() const
{
   // NOTE: may need adjusting
   switch (getAgeClass())
   {
   case NEW:
      return 0.f;
   case MID:
      return 0.02f;
   case OLD:
      return 0.05f;
   case VERYOLD:
   default:
      return 0.1f;
   }
}

Problem Property::createProblem() const
{
   std::string name = "broken something";
   int severity = getUniformRandomNumber(1,3);

   int TMP = 0;
   int cost_to_fix = TMP; // ************** come up with a cost metric for problems **************

   return { name, cost_to_fix, severity };
}

bool Property::rentPriceSuccess() const
{
   // if your set rental rate is more favorable 
   // to market rate then indicate a success
   return m_rental_price < OD::market.randomSalePrice(getAgeClass());
}

bool Property::salePriceSuccess() const
{
   // if your set sale price is more favorable 
   // to market price then indicate a success
   return m_price < OD::market.randomRentalRate(getAgeClass());
}

void Property::advanceDay()
{
   m_age++;

   if (m_looking_for_tenants)
   {
      // check market conditions, roll on chance for gaining renters
      if (rentPriceSuccess())
      {
         m_looking_for_tenants = false;
         m_rented = true;
      }
   }

   if (m_to_be_sold)
   {
      // check market conditions, roll on chance of sale
      // exit early if sold
      if (salePriceSuccess())
      {
         OD::Player::capital += m_price;
         deleteById(m_id, OD::Player::properties);
         return;
      }
   }

   // roll problems based on house age
   if (m_rented and getRandomEvent(getProblemChance()))
   {
      m_problem = createProblem();
   }

   // do manager things
   if (m_managed)
   {
      if (not m_rented) m_looking_for_tenants = true;

      // check for rent adjustments
      m_rental_price = OD::market.averageRentalRate(getAgeClass());

      // check for problems
      if (m_problem.has_value())
      {
         if (m_problem.value().cost_to_fix <= OD::Player::capital)
         {
            // if the player has the money to fix the problem then fix it
            OD::Player::capital -= m_problem.value().cost_to_fix;
            m_problem.reset();
         }
         else
         {
            // manager quit because you're poor
            // why don't you stop being poor
            m_managed = false;
         }
      }
   }

   // check tenant dissatisfaction (maybe they leave)

   // collect rent on rent day
   if (m_rented and OD::Date::getWeekday() == m_rent_day)
   {
      // get rent
      int collected_rent = m_rental_price;
      if (m_managed) collected_rent *= 0.9f; // manager takes 10% cut
      OD::Player::capital += collected_rent;
   }
}



} // namespace Game
