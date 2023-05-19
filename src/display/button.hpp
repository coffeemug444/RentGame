#pragma once
#include <SFML/Graphics.hpp>
#include "util/util.hpp"
#include "screen.hpp"


namespace Game
{

class Button
{
public:
   Button(Screen& callback_class, int button_id)
      :m_callback_class(callback_class) 
      ,m_button_id(button_id){}
   void click() { m_callback_class.handleClick(m_button_id); }
   virtual bool mouseIsOver(sf::Vector2i mouse_pos) const = 0;
private:
   Screen& m_callback_class;
   int m_button_id;
};

} // namespace Game