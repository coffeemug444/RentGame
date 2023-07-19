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
   Screen(Ui& ui, std::string title, sf::Color background_color);
   
   virtual void setSize(const sf::Vector2f& screen_size) override;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

   virtual void setActive(bool active) { m_active = active; }
   virtual bool getActive() const { return m_active; }
   
protected:
   Ui& m_ui;
   sf::RectangleShape m_background;
   sf::Font m_font;
   sf::Text m_title;
   sf::Vector2u m_screen_size;
   sf::Color m_background_color;
   bool m_active;
};

} // namespace Game
