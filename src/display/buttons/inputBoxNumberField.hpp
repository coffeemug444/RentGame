#pragma once
#include <SFML/Graphics.hpp>
#include "display/widgets/widget.hpp"
#include <string>

namespace Game
{


class InputBoxNumberField : public Widget
{
public:
   InputBoxNumberField(sf::Color active_background_colour, 
                       sf::Color inactive_background_colour, 
                       sf::Color text_colour, 
                       int font_size, 
                       int max_len = 10);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void addDigit(char digit);
   void backSpace();
   int getNumber() const;
   void setPosition(const sf::Vector2f& pos);
   bool mouseIsOver(sf::Vector2i mouse_pos) const;
   void mouseDown(sf::Vector2i mouse_pos) override;
   void mouseUp(sf::Vector2i mouse_pos) override;
   void setActive(bool active);
   void handleClick(int button_id) override {}
private:
   void setDisplay();
   bool m_active;
   bool m_last_mouse_down;
   std::string m_number;
   sf::Text m_number_display;
   sf::RectangleShape m_background_box;
   int m_max_len;
   sf::Vector2f m_text_offset;
   sf::Color m_active_background_colour;
   sf::Color m_inactive_background_colour;
};

   
} // namespace Game
