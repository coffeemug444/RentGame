#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "display/widgets/widget.hpp"

namespace Game
{

class Ui;
class Button;
class Widget;

class Screen : public Widget
{
public:
   Screen(Ui& ui, sf::Vector2u screen_size, std::string title, sf::Color background_color);
   
   virtual void setScreenSize(sf::Vector2u screen_size);
   sf::Vector2f getSize() const override;
   sf::Vector2f getPosition() const override;

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

   virtual void setActive(bool active) { m_active = active; }
   virtual bool getActive() const { return m_active; }

   virtual void mouseDown(sf::Vector2i mouse_pos) override;
   virtual void mouseUp(sf::Vector2i mouse_pos) override;

   virtual void charEntered(char c) {}
   virtual void backspace() {}
   virtual void uiEvents() override;
   virtual void dataSync() override;
   
   
protected:
   Ui& m_ui;
   sf::RectangleShape m_background;
   sf::Font m_font;
   sf::Text m_title;
   sf::Vector2u m_screen_size;
   sf::Color m_background_color;
   bool m_active;
   int m_last_button_id;
};

} // namespace Game
