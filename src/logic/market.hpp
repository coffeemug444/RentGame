#pragma once
#include "property.hpp"
#include <vector>

namespace Game
{


// to be in charge of determining supply and demand of housing
//
// determines "going price" of houses, which is a basis for checking
// if a house for sale will be sold, and is used for offering new houses
// for sale
//
// determines rental demand and the current "going price" of rentals for
// different house ages

class Market
{
public:
Market();
int averageSalePrice(Property::AgeClass age) const;
int averageRentalRate(Property::AgeClass age) const;
int randomSalePrice(Property::AgeClass age) const;
int randomRentalRate(Property::AgeClass age) const;
void advanceDay();

struct Listing
{
   unsigned id;
   int age; // listing age, not property age
   Property property;

   unsigned getId() const { return id; } // required for util vector helpers
};

const std::vector<Listing>& getListings() const { return m_listings; }
void purchaseListing(unsigned id);

private:
std::vector<Listing> m_listings;
inline static unsigned m_next_listing_id = 0;

int randomPropertyAge() const;
float getTimeModifier() const;
float getAgeModifier(Property::AgeClass age) const;

// NOTE: these may need adjustment
inline static const int m_initial_property_price = 1000;
inline static const int m_initial_rental_rate = 1000;

const int m_doubling_period;


// create new property
};


} // namespace Game
