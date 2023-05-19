#pragma once
#include <SFML/Graphics.hpp>
#include "util/util.hpp"


namespace Game
{

template <typename T>
class Button
{
public:
   Button(T& callback_class, void (T::*callback)())
      :m_callback_class(callback_class)
      ,m_callback(callback) {}
   void click() { (m_callback_class.*m_callback)(); }
   virtual bool mouseIsOver(sf::Vector2i mouse_pos) const = 0;
private:
   void (T::*m_callback)();
   T& m_callback_class;
};

} // namespace Game