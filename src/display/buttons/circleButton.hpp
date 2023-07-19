#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp"


namespace Game
{

class CircleButton : public Button
{
public:
   CircleButton(std::function<void(void)> callback, Widget::Alignment alignment = {TOP, LEFT})
      :Button(callback, alignment) {}
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(m_button_circle); };
   bool mouseIsOver(sf::Vector2i mouse_pos) const override
   {
      auto button_center = getPosition() 
                         + sf::Vector2f{getRadius(),
                                        getRadius()};
      sf::Vector2f d = button_center - mouse_pos;
      return ((d.x*d.x+d.y*d.y) < getRadius()*getRadius());
   }
   virtual float getRadius() const { return m_button_circle.getRadius(); }
   virtual void move(const sf::Vector2f& pos) override { Widget::move(pos); m_button_circle.move(pos); }
   virtual void setRadius(float radius) { m_button_circle.setRadius(radius); }
   virtual void setSize(const sf::Vector2f& container_size) override { 
      Widget::setSize(container_size);
      float r = std::min(container_size.x, container_size.y) / 2.f;
      m_button_circle.setPosition(getPosition());
      switch (m_alignment.horizontal)
      {
      case LEFT: break;
      case RIGHT: m_button_circle.move({getSize().x-2*r,0}); break;
      case H_CENTER: m_button_circle.move({(getSize().x/2.f)-r,0}); break;
      default: break;
      }
      switch (m_alignment.vertical)
      {
      case TOP: break;
      case BOTTOM: m_button_circle.move({0,getSize().y-2*r}); break;
      case V_CENTER: m_button_circle.move({0,(getSize().y/2.f)-r}); break;
      default: break;
      }

      setRadius(r);
    }
   virtual void setFillColor(const sf::Color& color) { m_button_circle.setFillColor(color); }
protected:
   sf::CircleShape m_button_circle;
};

} // namespace Game