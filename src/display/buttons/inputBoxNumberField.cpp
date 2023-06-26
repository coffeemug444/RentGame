#include "inputBoxNumberField.hpp"
#include "observableData.hpp"

namespace Game
{

InputBoxNumberField::InputBoxNumberField(sf::Color active_background_colour, 
                                         sf::Color inactive_background_colour, 
                                         sf::Color text_colour, 
                                         int font_size, 
                                         int max_len)
:m_active(false)
,m_last_mouse_down(false)
,m_number("0")
,m_max_len(max_len)
,m_active_background_colour(active_background_colour)
,m_inactive_background_colour(inactive_background_colour)
{
   m_number_display.setFont(OD::font);
   setDisplay();

   m_background_box.setFillColor(inactive_background_colour);
   m_number_display.setFillColor(text_colour); 

   m_number_display.setCharacterSize(font_size);
   m_background_box.setSize({font_size*max_len*0.7f, font_size*1.4f});

   m_text_offset = sf::Vector2f{0.1f*font_size,0.1f*font_size};
}

void InputBoxNumberField::addDigit(char digit)
{
   if (not m_active) return;
   if (m_number.size() == m_max_len) return;
   if (m_number == "0") m_number = digit;
   else m_number.push_back(digit);
   setDisplay();
}

void InputBoxNumberField::backSpace()
{
   if (not m_active) return;
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

bool InputBoxNumberField::mouseIsOver(sf::Vector2i mouse_pos) const
{
   return m_background_box.getGlobalBounds().contains({(float)mouse_pos.x, (float)mouse_pos.y});
} 

void InputBoxNumberField::mouseDown(sf::Vector2i mouse_pos) 
{
   m_last_mouse_down = mouseIsOver(mouse_pos);
}

void InputBoxNumberField::mouseUp(sf::Vector2i mouse_pos) 
{
   setActive(m_last_mouse_down and mouseIsOver(mouse_pos));
}

void InputBoxNumberField::setActive(bool active)
{
   m_active = active;
   m_background_box.setFillColor(active
                                 ? m_active_background_colour
                                 : m_inactive_background_colour
   );
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
