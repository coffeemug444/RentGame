#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Game
{


class InputBoxNumberField : public sf::Drawable
{
public:
   InputBoxNumberField(sf::Color background_colour, sf::Color text_colour, int font_size, int max_len = 10);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void addDigit(char digit);
   void backSpace();
   int getNumber() const;
   void setPosition(const sf::Vector2f& pos);
private:
   void setDisplay();
   std::string m_number;
   sf::Text m_number_display;
   sf::RectangleShape m_background_box;
   int m_max_len;
   sf::Vector2f m_text_offset;
};

   
} // namespace Game
