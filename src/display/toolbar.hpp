#pragma once
#include <SFML/Graphics.hpp>
#include "circleButton.hpp"
#include "screen.hpp"

namespace Game
{

class Ui;

   
class Toolbar : public Screen
{
public:
   Toolbar(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   bool mouseIsOver(sf::Vector2i mouse_pos) const;
private:
   void handleClick(int button_id) override;

   enum ButtonId {
      NONE = 0,
      FINANCE,
      PROPERTIES,
      LOANS,
      MARKET
   };

   Ui& m_ui;
   sf::Vector2u m_screen_size;
   sf::RectangleShape m_bar;
   CircleButton m_finance_button;
   CircleButton m_properties_button;
   CircleButton m_loans_button;
   CircleButton m_market_button;
   sf::Font m_font;
   sf::Text m_capital_display;
   sf::Text m_debt_display;
   sf::Text m_net_income_display;
};

} // namespace Game
