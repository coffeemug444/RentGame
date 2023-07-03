#pragma once
#include "property.hpp"

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
Market() {}
int propertySalePrice(AgeClass age) const;
int propertyRentalPrice(AgeClass age) const;

private:
// create new property
};


} // namespace Game
