#include "property.hpp"

namespace Game
{


Property::Property(unsigned id, int price, int age)
:m_id(id)
,m_price(price)
,m_age(age)
,m_rental_price(0)
,m_rented(false)
,m_renter_dissatisfaction(0)
,m_managed(false)
,m_to_be_rented(false)
,m_to_be_sold(false)
{
}



} // namespace Game
