#pragma once
#include <SFML/Graphics.hpp>
#include "display/buttons/circleButton.hpp"
#include "display/buttons/speedButton.hpp"
#include "display/widgets/widget.hpp"
#include "logic/gameLogic.hpp"

namespace Game
{

class Ui;

   
class Toolbar : public Widget
{
public:
   Toolbar(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   bool mouseIsOver(sf::Vector2i mouse_pos) const;
   sf::Vector2f getSize() const override;
   sf::Vector2f getPosition() const override;
   std::vector<const Button*> getButtons() const override;
   Iterator end() const override { return Iterator(this, 0); }
private:
   void handleClick(int button_id) override;

   enum ButtonId {
      NONE = 0,
      FINANCE,
      PROPERTIES,
      LOANS,
      MARKET,
      PAUSE,
      NORMAL,
      FAST,
      VERYFAST
   };

   Ui& m_ui;
   sf::Vector2u m_screen_size;
   sf::RectangleShape m_bar;
   mutable SpeedButton m_speed_pause;
   mutable SpeedButton m_speed_normal;
   mutable SpeedButton m_speed_fast;
   mutable SpeedButton m_speed_veryfast;
   CircleButton m_finance_button;
   CircleButton m_properties_button;
   CircleButton m_loans_button;
   CircleButton m_market_button;
   sf::Font m_font;
   mutable sf::Text m_capital_display;
   mutable sf::Text m_debt_display;
   mutable sf::Text m_net_income_display;
   mutable GameLogic::GameSpeed m_current_speed;
   int m_last_button_id;
};

} // namespace Game
