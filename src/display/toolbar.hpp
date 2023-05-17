#pragma once
#include <SFML/Graphics.hpp>

namespace Game
{

class Ui;
   
class Toolbar : public sf::Drawable
{
public:
   Toolbar(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size);
   sf::Cursor::Type getCursorType(sf::Vector2u mouse_pos);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
   Ui& m_ui;
   sf::Vector2u m_screen_size;
   sf::RectangleShape m_bar;
   sf::CircleShape m_button;
   sf::Font m_font;
   sf::Text m_capital_display;
   sf::Text m_debt_display;
   sf::Text m_net_income_display;
   unsigned m_capital = 123;
   unsigned m_debt = 456;
   unsigned m_net_income = 789;
};

} // namespace Game
