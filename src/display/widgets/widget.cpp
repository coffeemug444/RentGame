#include "widget.hpp"
#include "display/buttons/button.hpp"

namespace Game
{
   

Widget::Widget() 
:m_last_button_id(0) 
{}


sf::Cursor::Type Widget::getCursorType(sf::Vector2i mouse_pos) const
{
   static int hand_count = 0;

   for (auto& sub_widget : *this)
   {
      sf::Cursor::Type cursor_type = sub_widget.getCursorType(mouse_pos);
      if (cursor_type != sf::Cursor::Arrow) return cursor_type;
   }

   auto buttons = getButtons();
   for (auto button_ptr : buttons)
   {
      if (button_ptr->mouseIsOver(mouse_pos)) return sf::Cursor::Hand;
   }
   return sf::Cursor::Arrow;
}

void Widget::mouseDown(sf::Vector2i mouse_pos)
{
   for (auto& sub_widget : *this)
   {
      sub_widget.mouseDown(mouse_pos);
   }

   auto buttons = getButtons();
   for (auto button_ptr : buttons)
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
   for (auto& sub_widget : *this)
   {
      sub_widget.mouseUp(mouse_pos);
   }

   if (m_last_button_id == 0) return;
   auto buttons = getButtons();
   for (auto button_ptr : buttons)
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

void Widget::uiEvents()
{
   for (auto& sub_widget : *this)
   {
      sub_widget.uiEvents();
   }
}

void Widget::dataSync()
{
   for (auto& sub_widget : *this)
   {
      sub_widget.dataSync();
   }
}

void Widget::charEntered(char c)
{
   for (auto& sub_widget : *this)
   {
      sub_widget.charEntered(c);
   }
}

void Widget::backspace()
{
   for (auto& sub_widget : *this)
   {
      sub_widget.backspace();
   }
}

void Widget::setScreenSize(const sf::Vector2u& pos)
{
   for (auto& sub_widget : *this)
   {
      sub_widget.setScreenSize(pos);
   }
}

void Widget::setPosition(const sf::Vector2f& pos)
{
   sf::Vector2f old_pos = getPosition();
   sf::Vector2f diff = pos - old_pos;
   move(diff);
   for (auto& sub_widget : *this)
   {
      sub_widget.move(diff);
   }
}

void Widget::move(const sf::Vector2f& pos)
{
   for (auto& sub_widget : *this)
   {
      sub_widget.move(pos);
   }
}

void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   for (auto& sub_widget : *this)
   {
      target.draw(sub_widget);
   }
   auto buttons = getButtons();
   for (auto button_ptr : buttons)
   {
      target.draw(*button_ptr);
   }
}


} // namespace Game
