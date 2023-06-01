#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Game
{


class InputBoxNumberField : public sf::Drawable
{
public:
   InputBoxNumberField();
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void addDigit(char digit);
   void backSpace();
   int getNumber() const;
   void setPosition(const sf::Vector2f& pos) { m_number_display.setPosition(pos); }
private:
   void setDisplay();
   std::string m_number;
   sf::Text m_number_display;
};

   
} // namespace Game
