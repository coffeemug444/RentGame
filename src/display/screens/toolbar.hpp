#pragma once
#include <SFML/Graphics.hpp>
#include "display/buttons/circleButton.hpp"
#include "display/buttons/speedButton.hpp"
#include "display/widgets/widget.hpp"
#include "logic/gameLogic.hpp"
#include "display/widgets/textWidget.hpp"

namespace Game
{

class Ui;

   
class Toolbar : public Widget
{
public:
   Toolbar(Ui& ui);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   bool mouseIsOver(sf::Vector2i mouse_pos) const;
   void setSize(const sf::Vector2f& screen_size) override;
   void move (const sf::Vector2f& pos) override;
   const Widget& getSubWidget(unsigned index) const override;
   Iterator end() const override { return Iterator(this, 11); }
private:

   Ui& m_ui;
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
   mutable TextWidget m_capital_display;
   mutable TextWidget m_debt_display;
   mutable TextWidget m_net_income_display;
   mutable GameLogic::GameSpeed m_current_speed;
   int m_last_button_id;
};

} // namespace Game
