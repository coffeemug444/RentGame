#pragma once
#include <SFML/Graphics.hpp>
#include "display/buttons/button.hpp"


namespace Game
{

class CircleButton : public Button, public sf::CircleShape
{
public:
   CircleButton(Screen& callback_class, int button_id)
      :Button(callback_class, button_id) {}
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