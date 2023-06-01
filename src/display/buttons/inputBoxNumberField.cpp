#include "inputBoxNumberField.hpp"
#include "observableData.hpp"
#include <iostream>

namespace Game
{

InputBoxNumberField::InputBoxNumberField(sf::Color background_colour, sf::Color text_colour, int font_size, int max_len)
:m_number("0")
,m_max_len(max_len)
{
   m_number_display.setFont(OD::font);
   setDisplay();

   m_background_box.setFillColor(background_colour);
   m_number_display.setFillColor(text_colour); 

   m_number_display.setCharacterSize(font_size);
   m_background_box.setSize({font_size*max_len*0.7f, font_size*1.4f});

   m_text_offset = sf::Vector2f{0.1f*font_size,0.1f*font_size};
}

void InputBoxNumberField::addDigit(char digit)
{
   if (m_number.size() == m_max_len) return;
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

void InputBoxNumberField::setPosition(const sf::Vector2f& pos) 
{ 
   m_background_box.setPosition(pos);
   m_number_display.setPosition(pos+m_text_offset); 
}

void InputBoxNumberField::setDisplay()
{
   m_number_display.setString(m_number);
}

void InputBoxNumberField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_background_box);
   target.draw(m_number_display);
}
   
} // namespace Game
