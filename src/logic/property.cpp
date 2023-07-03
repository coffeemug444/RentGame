#include "property.hpp"
#include "observableData.hpp"

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



void Property::advanceDay()
{
   if (m_to_be_rented)
   {
      // check market conditions, roll on chance for gaining renters
   }

   if (m_to_be_sold)
   {
      // check market conditions, roll on chance of sale
      // exit early if sold
   }

   if (m_rented)
   {
      // roll problems

      if (m_managed)
      {
         // check for rent adjustments
      }
      else
      {

      }

      // check tenant dissatisfaction (maybe they leave)

      if (OD::Date::day % OD::Date::MONTH_LEN == m_rent_day)
      {
         // get rent
         OD::Player::capital += m_rental_price;
      }
   }
}



} // namespace Game
