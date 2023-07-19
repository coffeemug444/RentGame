#pragma once
#include <SFML/Graphics.hpp>
#include "display/widgets/widget.hpp"
#include <string>

namespace Game
{


class InputBoxNumberField : public Widget
{
public:
   InputBoxNumberField(std::string label,
                       sf::Color active_background_colour, 
                       sf::Color inactive_background_colour, 
                       sf::Color text_colour, 
                       int font_size, 
                       int max_len = 10); // 1`000`000`000, N billion
   void setError(std::string error_message);
   void resetError();
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void charEntered(char c) override;
   void backspace() override;
   void reset();
   int getNumber() const;
   void setNumber(int number);
   void setSize(const sf::Vector2f& size) override;
   void move(const sf::Vector2f& pos) override;
   bool mouseIsOver(sf::Vector2i mouse_pos) const;
   void mouseDown(sf::Vector2i mouse_pos) override;
   void mouseUp(sf::Vector2i mouse_pos) override;
   void setActive(bool active);
   void setEditable(bool editable);
   Iterator end() const override { return Iterator(this, 0); }
private:
   void setDisplay();
   bool m_editable;
   bool m_active;
   bool m_last_mouse_down;
   std::string m_number;
   int m_font_size;
   sf::Text m_label;
   sf::Text m_errors;
   sf::Text m_number_display;
   sf::RectangleShape m_background_box;
   int m_max_len;
   sf::Vector2f m_text_offset;
   sf::Color m_active_background_colour;
   sf::Color m_inactive_background_colour;
};

   
} // namespace Game
