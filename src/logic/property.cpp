#include "property.hpp"
#include "observableData.hpp"
#include "util/util.hpp"

namespace Game
{


Property::Property(unsigned id, int price, int age)
:m_id(id)
,m_price(price)
,m_age(age)
,m_rental_price(0)
,m_rented(false)
,m_rent_day(0)
,m_renter_dissatisfaction(0)
,m_managed(false)
,m_to_be_rented(false)
,m_to_be_sold(false)
{
}

AgeClass Property::getAgeClass() const
{
   // NOTE: may need adjusting
   if (m_age <= 2) return NEW;
   if (m_age <= 5) return MID;
   if (m_age <= 7) return OLD;
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

float Property::getRenterChance() const
{
   // look at market conditions
   float TMP = 0.f;
   return TMP;
}

float Property::getSaleChance() const
{
   // look at market conditions
   float TMP = 0.f;
   return TMP;
}

void Property::advanceDay()
{
   if (m_to_be_rented)
   {
      // check market conditions, roll on chance for gaining renters
      if (getRandomEvent(getRenterChance()))
      {
         m_to_be_rented = false;
         m_rented = true;
      }
   }

   if (m_to_be_sold)
   {
      // check market conditions, roll on chance of sale
      // exit early if sold
      if (getRandomEvent(getSaleChance()))
      {
         OD::Player::capital += m_price;
         deleteById(m_id, OD::Player::properties);
         return;
      }
   }

   if (not m_rented) return;

   // roll problems based on house age
   if (getRandomEvent(getProblemChance()))
   {
      m_problem = createProblem();
   }

   // do manager things
   if (m_managed)
   {
      // check for rent adjustments

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
   if (OD::Date::day % OD::Date::WEEK_LEN == m_rent_day)
   {
      // get rent
      int collected_rent = m_rental_price;
      if (m_managed) collected_rent *= 0.9f; // manager takes 10% cut
      OD::Player::capital += collected_rent;
   }
}



} // namespace Game
