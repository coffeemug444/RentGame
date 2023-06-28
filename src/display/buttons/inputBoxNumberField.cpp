#include "inputBoxNumberField.hpp"
#include "observableData.hpp"
#include "display/constColors.hpp"

namespace Game
{

InputBoxNumberField::InputBoxNumberField(std::string label,
                                         sf::Color active_background_colour, 
                                         sf::Color inactive_background_colour, 
                                         sf::Color text_colour, 
                                         int font_size, 
                                         int max_len)
:m_active(false)
,m_last_mouse_down(false)
,m_number("0")
,m_font_size(font_size)
,m_max_len(max_len)
,m_active_background_colour(active_background_colour)
,m_inactive_background_colour(inactive_background_colour)
{
   m_number_display.setFont(OD::font);
   setDisplay();

   m_label.setString(label);
   m_label.setFont(OD::font);
   m_label.setCharacterSize(font_size);

   m_errors.setFont(OD::font);
   m_errors.setCharacterSize(font_size);
   m_errors.setFillColor(sf::Color::Red);

   m_background_box.setFillColor(inactive_background_colour);
   m_number_display.setFillColor(text_colour); 

   m_number_display.setCharacterSize(font_size);
   float background_box_w = font_size*max_len*0.7f;
   m_background_box.setSize({background_box_w, font_size*1.4f});

   m_text_offset = sf::Vector2f{0.1f*font_size,0.1f*font_size};

   sf::Vector2f numbers_offset {20*m_font_size,0};
   
   m_background_box.setPosition(numbers_offset);
   m_number_display.setPosition(numbers_offset+m_text_offset); 
   m_errors.setPosition(numbers_offset+sf::Vector2f{background_box_w+0.5f,0});
}

void InputBoxNumberField::addDigit(char digit)
{
   if (not m_active) return;
   if (m_number.size() == m_max_len) return;
   if (m_number == "0") m_number = digit;
   else m_number.push_back(digit);
   setDisplay();
}

void InputBoxNumberField::reset()
{
   m_active = false;
   m_number = "0";
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

void InputBoxNumberField::move(const sf::Vector2f& pos)
{ 
   m_label.move(pos);
   m_background_box.move(pos);
   m_number_display.move(pos);
   m_errors.move(pos);
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

sf::Vector2f InputBoxNumberField::getSize() const
{
   return m_background_box.getSize();
}

sf::Vector2f InputBoxNumberField::getPosition() const
{
   return m_label.getPosition();
}

void InputBoxNumberField::setDisplay()
{
   m_number_display.setString(m_number);
}

void InputBoxNumberField::setError(std::string error_message)
{
   m_errors.setString(error_message);
}

void InputBoxNumberField::resetError()
{
   m_errors.setString("");
}

void InputBoxNumberField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_label);
   target.draw(m_background_box);
   target.draw(m_number_display);
   target.draw(m_errors);
}
   
} // namespace Game
