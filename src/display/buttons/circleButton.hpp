#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"


namespace Game
{

class CircleButton : public Button
{
public:
   CircleButton(std::function<void(void)> callback)
      :Button(callback) {}
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(m_button_circle); };
   bool mouseIsOver(sf::Vector2i mouse_pos) const override
   {
      auto button_center = getPosition() 
                         + sf::Vector2f{getRadius(),
                                        getRadius()};
      sf::Vector2f d = button_center - mouse_pos;
      return ((d.x*d.x+d.y*d.y) < getRadius()*getRadius());
   }
   sf::Vector2f getPosition() const override { return m_button_circle.getPosition(); }
   virtual float getRadius() const { return m_button_circle.getRadius(); }
   virtual sf::Vector2f getSize() const override {
      float r = getRadius();
      return {2*r,2*r};
   }
   virtual void move(const sf::Vector2f& pos) override { m_button_circle.move(pos); }
   virtual void setRadius(float radius) { m_button_circle.setRadius(radius); }
   virtual void setFillColor(const sf::Color& color) { m_button_circle.setFillColor(color); }
private:
   sf::CircleShape m_button_circle;
};

} // namespace Game