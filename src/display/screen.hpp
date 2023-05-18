#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Game
{

class Ui;

class Screen : public sf::Drawable
{
public:
   Screen(Ui& ui, sf::Vector2u screen_size, std::string title, sf::Color background_color);
   
   virtual sf::Cursor::Type getCursorType(sf::Vector2u mouse_pos) const = 0;
   virtual void setScreenSize(sf::Vector2u screen_size);

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

   void setActive(bool active) { m_active = active; }

   virtual void mouseDown(sf::Vector2i mouse_pos) {}
   virtual void mouseUp(sf::Vector2i mouse_pos) {}
   
   
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
