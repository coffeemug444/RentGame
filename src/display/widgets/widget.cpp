#include "widget.hpp"
#include "display/buttons/button.hpp"

namespace Game
{
   

sf::Cursor::Type Widget::getCursorType(sf::Vector2i mouse_pos) const
{
   for (auto& sub_widget : *this)
   {
      sf::Cursor::Type cursor_type = sub_widget.getCursorType(mouse_pos);
      if (cursor_type != sf::Cursor::Arrow) return cursor_type;
   }
   return sf::Cursor::Arrow;
}

void Widget::mouseDown(sf::Vector2i mouse_pos)
{
   for (auto& sub_widget : *this)
   {
      sub_widget.mouseDown(mouse_pos);
   }
}

void Widget::mouseUp(sf::Vector2i mouse_pos)
{
   for (auto& sub_widget : *this)
   {
      sub_widget.mouseUp(mouse_pos);
   }
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

void Widget::setSize(const sf::Vector2f& container_size)
{
   m_container_size = container_size;
   setSubWidgetSize();
   placeSubWidgets();
}

void Widget::setSubWidgetSize()
{
   auto sub_widget_size = m_container_size;
   unsigned num_sub_widgets = end() - begin();
   if (m_placement_style == ROW) sub_widget_size.y /= num_sub_widgets;
   else                          sub_widget_size.x /= num_sub_widgets;

   for (auto& sub_widget : *this)
   {
      sub_widget.setSize(sub_widget_size);
   }
}

void Widget::placeSubWidgets()
{
   sf::Vector2f sub_widget_pos = getPosition();
   for (auto& sub_widget : *this)
   {
      sub_widget.setPosition(sub_widget_pos);
      sf::Vector2f sub_widget_size = sub_widget.getSize();
      if (m_placement_style == ROW) sub_widget_pos.y += sub_widget_size.y;
      else                          sub_widget_pos.x += sub_widget_size.x;
   }
}

void Widget::setPosition(const sf::Vector2f& pos)
{
   sf::Vector2f diff = pos - m_position;
   move(diff);
}

void Widget::move(const sf::Vector2f& diff)
{
   m_position += diff;
   for (auto& sub_widget : *this)
   {
      sub_widget.move(diff);
   }
}

void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   for (auto& sub_widget : *this)
   {
      target.draw(sub_widget);
   }
}


} // namespace Game
