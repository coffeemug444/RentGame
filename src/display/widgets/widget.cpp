#include "widget.hpp"
#include "display/buttons/button.hpp"

namespace Game
{
   

Widget::Widget(const std::vector<Button*>& buttons) 
:m_buttons(buttons)
,m_last_button_id(0) 
{}


sf::Cursor::Type Widget::getCursorType(sf::Vector2i mouse_pos) const
{
   auto sub_widgets = getSubWidgets();
   for (auto widget_ptr : sub_widgets)
   {
      sf::Cursor::Type cursor_type = widget_ptr->getCursorType(mouse_pos);
      if (cursor_type != sf::Cursor::Arrow) return cursor_type;
   }

   for (auto button_ptr : m_buttons)
   {
      if (button_ptr->mouseIsOver(mouse_pos)) return sf::Cursor::Hand;
   }
   return sf::Cursor::Arrow;
}

void Widget::mouseDown(sf::Vector2i mouse_pos)
{
   auto sub_widgets = getSubWidgets();
   for (auto widget_ptr : sub_widgets)
   {
      widget_ptr->mouseDown(mouse_pos);
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

void Widget::mouseUp(sf::Vector2i mouse_pos)
{
   auto sub_widgets = getSubWidgets();
   for (auto widget_ptr : sub_widgets)
   {
      widget_ptr->mouseUp(mouse_pos);
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

void Widget::setScreenSize(const sf::Vector2f& pos)
{
   auto sub_widgets = getSubWidgets();
   for (auto widget_ptr : sub_widgets)
   {
      widget_ptr->setScreenSize(pos);
   }
}

void Widget::setPosition(const sf::Vector2f& pos)
{
   sf::Vector2f old_pos = getPosition();
   sf::Vector2f diff = pos - old_pos;
   move(diff);
   auto sub_widgets = getSubWidgets();
   for (auto widget_ptr : sub_widgets)
   {
      widget_ptr->move(diff);
   }
}

void Widget::move(const sf::Vector2f& pos)
{
   auto sub_widgets = getSubWidgets();
   for (auto widget_ptr : sub_widgets)
   {
      widget_ptr->move(pos);
   }
}

void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   auto sub_widgets = getSubWidgets();
   for (auto widget_ptr : sub_widgets)
   {
      target.draw(*widget_ptr);
   }
   for (auto button_ptr : m_buttons)
   {
      target.draw(*button_ptr);
   }
}


} // namespace Game
