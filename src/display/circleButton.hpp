#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"


namespace Game
{

template <typename T>
class CircleButton : public Button<T>, public sf::CircleShape
{
public:
   CircleButton(T& callback_class, void (T::*callback)())
      :Button<T>(callback_class, callback) {}
   bool mouseIsOver(sf::Vector2i mouse_pos) const override
   {
      auto button_center = getPosition() 
                         + sf::Vector2f{getRadius(),
                                        getRadius()};
      sf::Vector2f d = button_center - mouse_pos;
      return ((d.x*d.x+d.y*d.y) < getRadius()*getRadius());
   }
};

} // namespace Game