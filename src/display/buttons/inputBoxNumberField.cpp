#include "inputBoxNumberField.hpp"
#include "observableData.hpp"
#include <iostream>

namespace Game
{

InputBoxNumberField::InputBoxNumberField()
:m_number("0")
{
   m_number_display.setFont(OD::font);
   setDisplay();
}

void InputBoxNumberField::addDigit(char digit)
{
   if (m_number.size() == 10) return;
   if (m_number == "0") m_number = digit;
   else m_number.push_back(digit);
   setDisplay();
}

void InputBoxNumberField::backSpace()
{
   if (m_number == "0") return;
   if (m_number.size() == 1) m_number = "0";
   else m_number.pop_back();
   setDisplay();
}

int InputBoxNumberField::getNumber() const
{
   return std::stoi(m_number);
}

void InputBoxNumberField::setDisplay()
{
   m_number_display.setString(m_number);
}

void InputBoxNumberField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_number_display);
}
   
} // namespace Game
