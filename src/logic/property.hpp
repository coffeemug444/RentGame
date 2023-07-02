#pragma once
#include <optional>




namespace Game
{

class Property
{
public:
Property(unsigned id, int price);
unsigned getId() const { return m_id; }
int getPrice() const { return m_price; }


private:
unsigned m_id;
int m_price;
// std::optional<Renter> m_renter;
// std::optional<Manager> m_manager;


};



} // namespace Game
