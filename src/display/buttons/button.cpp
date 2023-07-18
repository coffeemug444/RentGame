#include "button.hpp"
#include "logic/events/eventInterface.hpp"


namespace Game
{


void Button::mouseUp(sf::Vector2i mouse_pos) {
   if (m_pressed and mouseIsOver(mouse_pos)) {
      std::lock_guard lock(EI::gametick_mutex);
      m_callback();
   }
   m_pressed = false;
}

sf::Cursor::Type Button::getCursorType(sf::Vector2i mouse_pos) const 
{
   if (mouseIsOver(mouse_pos)) return sf::Cursor::Hand;
   return sf::Cursor::Arrow;
}
   
} // namespace Game
