#pragma once
#include <SFML/Graphics.hpp>
#include "util/util.hpp"


namespace Game
{

template <typename T>
class Button : public sf::CircleShape
{
public:
   Button(T& callback_class, void (T::*callback)())
      :m_callback_class(callback_class)
      ,m_callback(callback) {}
   void click() { (m_callback_class.*m_callback)(); }
   bool mouseIsOver(sf::Vector2i mouse_pos) const
   {
      auto button_center = getPosition() 
                         + sf::Vector2f{getRadius(),
                                        getRadius()};
      sf::Vector2f d = button_center - mouse_pos;
      return ((d.x*d.x+d.y*d.y) < getRadius()*getRadius());
   }
private:
   void (T::*m_callback)();
   T& m_callback_class;
};

} // namespace Game