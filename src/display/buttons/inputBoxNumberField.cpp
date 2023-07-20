#include "inputBoxNumberField.hpp"
#include "observableData.hpp"
#include "display/constColors.hpp"
#include "util/util.hpp"

namespace Game
{

InputBoxNumberField::InputBoxNumberField(sf::Color active_background_colour, 
                                         sf::Color inactive_background_colour, 
                                         sf::Color text_colour, 
                                         int font_size, 
                                         int max_len)
:m_editable(true)
,m_active(false)
,m_last_mouse_down(false)
,m_number("0")
,m_font_size(font_size)
,m_max_len(max_len)
,m_active_background_colour(active_background_colour)
,m_inactive_background_colour(inactive_background_colour)
{
   setDisplay();
   m_background_box.setFillColor(inactive_background_colour);
   m_number_display.setFillColor(text_colour); 
}

void InputBoxNumberField::charEntered(char digit)
{
   if (not m_active) return;
   if (m_number.size() == m_max_len) return;
   if ('0' > digit or '9' < digit) return;
   if (m_number == "0") m_number = digit;
   else m_number.push_back(digit);
   setDisplay();
}

void InputBoxNumberField::setSize(const sf::Vector2f& size)
{
   Widget::setSize(size);
   m_background_box.setSize(size - m_padding);
   m_background_box.setPosition(getPosition());
   m_background_box.move({m_padding.left, m_padding.top});
}

void InputBoxNumberField::setNumber(int number)
{
   m_number = std::to_string(number);
   setDisplay();
}

void InputBoxNumberField::reset()
{
   m_active = false;
   m_number = "0";
   setDisplay();
}

void InputBoxNumberField::backspace()
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

void InputBoxNumberField::move(const sf::Vector2f& pos)
{ 
   Widget::move(pos);
   m_background_box.move(pos);
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
   if (not m_editable) return;
   m_active = active;
   m_background_box.setFillColor(active
                                 ? m_active_background_colour
                                 : m_inactive_background_colour
   );
}

void InputBoxNumberField::setEditable(bool editable) 
{ 
   m_editable = editable; 
   if (not m_editable) m_active = false;
}

void InputBoxNumberField::setDisplay()
{
   m_number_display.setString(m_number);
}

void InputBoxNumberField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_background_box);
   Widget::draw(target, states);
}
   
} // namespace Game
