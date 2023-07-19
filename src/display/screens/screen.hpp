#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "display/widgets/widget.hpp"

namespace Game
{

class Ui;
class Widget;

class Screen : public Widget
{
public:
   Screen(std::string title, sf::Color background_color);
   
   virtual void setSize(const sf::Vector2f& screen_size) override;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

   virtual void setActive(bool active) { m_active = active; }
   virtual bool getActive() const { return m_active; }
   
protected:
   sf::RectangleShape m_background;
   sf::Text m_title;
   sf::Color m_background_color;
   bool m_active;
};

} // namespace Game
