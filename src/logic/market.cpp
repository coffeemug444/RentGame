#include "market.hpp"
#include "observableData.hpp"
#include "util/util.hpp"
#include <math.h>

namespace Game
{

Market::Market() : m_doubling_period(OD::Date::YEAR_LEN) {}

void Market::advanceDay()
{
   for (int i = 0; i < m_listings.size(); i++)
   {
      if (++(m_listings[i].age) >= 3)
      {
         m_listings.erase(m_listings.begin() + i);
         i--;
      }
   }
   while (m_listings.size() < 5)
   {
      int property_age = randomPropertyAge();
      Listing listing {
         .id{m_next_listing_id},
         .age{0},
         .property{
            property_age,
            randomSalePrice(Property::getAgeClass(property_age))
         }
      };
      m_listings.push_back(listing);
   }
}

void Market::purchaseListing(unsigned id)
{
   auto listing = findById(id, m_listings);
   if (not listing.has_value()) return;
   if (OD::Player::capital < listing.value()->property.getPrice()) return;
   OD::Player::capital -= listing.value()->property.getPrice();
   OD::Player::properties.push_back(listing.value()->property);
   deleteById(id, m_listings);
}

// gets a normally random distributed age with a 10% chance
// of getting a very old house
int Market::randomPropertyAge() const
{
   // in a normal distribution there is a 5% chance of getting a number greater than this
   const float NORMAL_5_PERCENT = 1.65f; 
   const int very_old_age_days = Property::AgeClass::VERYOLD*OD::Date::YEAR_LEN;
   return NORMAL_5_PERCENT * std::abs(getNormalRandomNumber()) * very_old_age_days;
}

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
