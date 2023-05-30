#pragma once
#include <SFML/Graphics.hpp>
#include "util/util.hpp"
#include "display/widgets/widget.hpp"

namespace Game
{


class Button : public sf::Drawable
{
public:
   Button(Widget& callback_class, int button_id)
      :m_callback_class(callback_class) 
      ,m_button_id(button_id){}
   void click() { m_callback_class.handleClick(m_button_id); }
   int getId() const { return m_button_id; }
   virtual bool mouseIsOver(sf::Vector2i mouse_pos) const = 0;
private:
   Widget& m_callback_class;
   int m_button_id;
};

} // namespace Game