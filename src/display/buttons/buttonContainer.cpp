#include "buttonContainer.hpp"
#include "button.hpp"

namespace Game
{
   

ButtonContainer::ButtonContainer(const std::vector<Button*>& buttons, const std::vector<ButtonContainer*>& sub_containers) 
:m_buttons(buttons)
,m_sub_containers(sub_containers)
,m_last_button_id(0) 
{}


sf::Cursor::Type ButtonContainer::getCursorType(sf::Vector2i mouse_pos) const
{
   for (auto container_ptr : m_sub_containers)
   {
      sf::Cursor::Type cursor_type = container_ptr->getCursorType(mouse_pos);
      if (cursor_type != sf::Cursor::Arrow) return cursor_type;
   }

   for (auto button_ptr : m_buttons)
   {
      if (button_ptr->mouseIsOver(mouse_pos)) return sf::Cursor::Hand;
   }
   return sf::Cursor::Arrow;
}

void ButtonContainer::mouseDown(sf::Vector2i mouse_pos)
{
   for (auto container_ptr : m_sub_containers)
   {
      container_ptr->mouseDown(mouse_pos);
   }

   for (auto button_ptr : m_buttons)
   {
      if (button_ptr->mouseIsOver(mouse_pos))
      {
         m_last_button_id = button_ptr->getId();
         return;
      }
   }
   m_last_button_id = 0;
}

void ButtonContainer::mouseUp(sf::Vector2i mouse_pos)
{
   for (auto container_ptr : m_sub_containers)
   {
      container_ptr->mouseUp(mouse_pos);
   }

   if (m_last_button_id == 0) return;
   for (auto button_ptr : m_buttons)
   {
      if (button_ptr->mouseIsOver(mouse_pos))
      {
         if (m_last_button_id == button_ptr->getId())
         {
            handleClick(m_last_button_id);
            break;
         }
      }
   }
   m_last_button_id = 0;
}


} // namespace Game
