#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace Game
{

class Ui;
class Button;

class Screen : public sf::Drawable
{
public:
   Screen(Ui& ui, sf::Vector2u screen_size, std::string title, sf::Color background_color, std::vector<Button*> buttons = {});
   
   virtual void handleClick(int button_id) {}

   virtual sf::Cursor::Type getCursorType(sf::Vector2i mouse_pos) const;
   virtual void setScreenSize(sf::Vector2u screen_size);

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

   virtual void setActive(bool active) { m_active = active; }

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
   std::vector<Button*> m_buttons;
};

} // namespace Game
