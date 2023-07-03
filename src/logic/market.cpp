#include "market.hpp"
#include "observableData.hpp"
#include <math.h>

namespace Game
{

Market::Market() : m_doubling_period(OD::Date::YEAR_LEN) {}

float Market::getTimeModifier() const
{
   return std::exp(OD::Date::day*M_LN2/m_doubling_period);
}

float Market::getAgeModifier(Property::AgeClass age) const
{
   // NOTE: may need adjusting
   switch (age)
   {
   case Property::AgeClass::NEW:
      return 2.f;
   case Property::AgeClass::MID:
      return 1.6f;
   case Property::AgeClass::OLD:
      return 1.2f;
   case Property::AgeClass::VERYOLD:
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
