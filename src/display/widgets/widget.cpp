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
   sub_widget_size.x -= m_padding.horizontal();
   sub_widget_size.y -= m_padding.vertical();
   unsigned num_sub_widgets = end() - begin();
   if (m_placement_style == ROW) sub_widget_size.y /= num_sub_widgets;
   else                          sub_widget_size.x /= num_sub_widgets;

   for (auto& sub_widget : *this)
   {
      sub_widget.setSize(sub_widget_size);
   }
}


// rows need to be placed on top of eachother
//    if colStyle and right aligned go backwards
// cols need to be placed side by side
//    if rowStyle and bottom aligned need to go backwards

// right alignment needs to know total width only if
// this is a colStyle

// bottom alignment needs to know total height only if
// this is a rowStyle

// center alignment needs to know total width for colStyles
// and total height for rowStyles
void Widget::placeSubWidgets()
{
   bool backwards = (m_placement_style == COL ? 
                        m_alignment.horizontal == RIGHT :   // right aligned cols 
                        m_alignment.vertical == BOTTOM );   // bottom aligned rows

   float total_width{0.f}, total_height{0.f};
   // if the total width/height of all widgets is required
   if ((m_alignment.horizontal == H_CENTER and m_placement_style == COL) or 
       (m_alignment.vertical == V_CENTER and m_placement_style == ROW)) {
      for (auto& sub_widget : *this)
      {
         auto size = sub_widget.getSize();
         total_width += size.x;
         total_height += size.y;
      }
   }

   auto this_size = getSize();
   this_size.x -= m_padding.horizontal();
   this_size.y -= m_padding.vertical();
   auto this_pos = getPosition();
   this_pos.x += m_padding.left;
   this_pos.y += m_padding.top;

   float x = this_pos.x;
   float y = this_pos.y;  

   auto get_x = [this_pos, this_size, x](sf::Vector2f sub_widget_size, Widget::Alignment alignment){
      if (alignment.horizontal == H_CENTER) {return this_pos.x + (this_size.x - sub_widget_size.x)/2.f;}
      else if (alignment.horizontal == RIGHT) {return this_pos.x + this_size.x - sub_widget_size.x;}
      else {return x;} // do nothing, it's already left aligned
   };
   auto get_y = [this_pos, this_size, y](sf::Vector2f sub_widget_size, Widget::Alignment alignment){
      if (alignment.vertical == V_CENTER) {return this_pos.y + (this_size.y - sub_widget_size.y)/2.f;}
      else if (alignment.vertical == BOTTOM) {return this_pos.y + this_size.y - sub_widget_size.y;}
      else {return y;} // do nothing, it's already top aligned
   };

   if (backwards)
   {
      if (m_placement_style == ROW) 
         x += this_size.x; // starting from the right
      else                          
         y += this_size.y; // starting from the bottom

      auto it = end();
      while (it != begin()) {
         --it;
         auto& sub_widget = *it;
         sf::Vector2f sub_widget_size = sub_widget.getSize();
         if (m_placement_style == ROW) // bottom to top
         {
            y -= sub_widget_size.y;
            x = get_x(sub_widget_size, m_alignment);
         }
         else // col placement, right to left
         {
            x -= sub_widget_size.x;
            y = get_y(sub_widget_size, m_alignment);
         }
         sub_widget.setPosition({x,y});
      }
   }
   else
   {
      // if row and center then start from (h_middle of this widget) - (half of total width of subwidgets)
      // if col and center then start from (v_middle of this widget) - (half of total height of subwidgets)
      if (m_placement_style == ROW and m_alignment.vertical == V_CENTER)
      {
         x += (this_size.x - total_width)/2.f;
      }
      if (m_placement_style == COL and m_alignment.horizontal == H_CENTER)
      {
         y += (this_size.y - total_height)/2.f;
      }

      for (auto& sub_widget : *this)
      {
         sf::Vector2f sub_widget_size = sub_widget.getSize();
         if (m_placement_style == ROW) // top to bottom
         {
            x = get_x(sub_widget_size, m_alignment);
         }
         else // col placement, right to left
         {
            y = get_y(sub_widget_size, m_alignment);
         }

         sub_widget.setPosition({x,y});

         if (m_placement_style == ROW) // top to bottom
            y += sub_widget_size.y;
         else
            x += sub_widget_size.x;
      }
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
