#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"


namespace Game
{

class CircleButton : public Button, public sf::Drawable
{
public:
   CircleButton(Screen& callback_class, int button_id)
      :Button(callback_class, button_id) {}
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(m_button_circle); };
   bool mouseIsOver(sf::Vector2i mouse_pos) const override
   {
      auto button_center = getPosition() 
                         + sf::Vector2f{getRadius(),
                                        getRadius()};
      sf::Vector2f d = button_center - mouse_pos;
      return ((d.x*d.x+d.y*d.y) < getRadius()*getRadius());
   }
   const sf::Vector2f& getPosition() const { return m_button_circle.getPosition(); }
   float getRadius() const { return m_button_circle.getRadius(); }
   void setPosition(const sf::Vector2f& pos) { m_button_circle.setPosition(pos); }
   void setRadius(float radius) { m_button_circle.setRadius(radius); }
   void setFillColor(const sf::Color& color) { m_button_circle.setFillColor(color); }
private:
   sf::CircleShape m_button_circle;
};

} // namespace Game