#include "market.hpp"
#include <math.h>

namespace Game
{


float Market::getTimeModifier() const
{
   return std::exp(OD::Date::day*M_LN2/m_doubling_period);
}

float Market::getAgeModifier(Property::AgeClass age) const
{
   // NOTE: may need adjusting
   switch (age)
   {
   case NEW:
      return 2.f;
   case MID:
      return 1.6f;
   case OLD:
      return 1.2f;
   case VERYOLD:
   default:
      return 1.f;
   }
}

int Market::propertySalePrice(Property::AgeClass age) const
{
   return getTimeModifier() * getAgeModifier(age) * m_initial_property_price;
}

int Market::propertyRentalPrice(Property::AgeClass age) const
{
   return getTimeModifier() * getAgeModifier(age) * m_initial_rental_price;
}

   
} // namespace Game
