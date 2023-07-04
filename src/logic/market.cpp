#include "market.hpp"
#include "observableData.hpp"
#include "util/util.hpp"
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

int Market::averageSalePrice(Property::AgeClass age) const
{
   return getTimeModifier() * getAgeModifier(age) * m_initial_property_price;
}

int Market::averageRentalRate(Property::AgeClass age) const
{
   return getTimeModifier() * getAgeModifier(age) * m_initial_rental_rate;
}

int Market::randomSalePrice(Property::AgeClass age) const
{
   int going_sale_price = averageSalePrice(age);
   float random = getNormalRandomNumber();
   random *= std::log((float)going_sale_price);
   random += going_sale_price;
   return (int)random;
}

int Market::randomRentalRate(Property::AgeClass age) const
{
   int going_rental_rate = averageRentalRate(age);
   float random = getNormalRandomNumber();
   random *= std::log((float)going_rental_rate);
   random += going_rental_rate;
   return (int)random;
}

   
} // namespace Game
