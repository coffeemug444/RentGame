#pragma once
#include <string>
#include <optional>




namespace Game
{


struct Problem
{
   std::string name;
   int cost_to_fix;
   int severity;
};

class Property
{
public:
Property(unsigned id, int price, int age);
unsigned getId() const { return m_id; }
int getPrice() const { return m_price; }
std::optional<Problem> getProblem() const { return m_problem; }
void advanceDay();

enum AgeClass
{
   NEW,
   MID,
   OLD,
   VERYOLD
};

AgeClass getAgeClass() const;


private:
Problem createProblem() const;
float getProblemChance() const;

// queries the market for going rates and decides if the current
// set price will result in a successfully finding a buyer/renter
// based on some random fluctuations
bool rentPriceSuccess() const;
bool salePriceSuccess() const;

unsigned m_id;
int m_price;
int m_age; // age in days. older properties get problems more frequently
int m_rental_price;

// only 1 problem at a time, but low severity problems 
// can be overridden by higher severity problems
std::optional<Problem> m_problem; 

bool m_rented;
int m_rent_day; // day of the week that rent is due
int m_renter_dissatisfaction;

// automated management of property eg. rent price, fixing problems
bool m_managed; 

bool m_to_be_rented;   // player is looking for tenants
bool m_to_be_sold;  // player is looking for buyers


};



} // namespace Game
