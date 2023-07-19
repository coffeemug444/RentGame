#pragma once
#include <SFML/Graphics.hpp>
#include "display/buttons/circleButton.hpp"
#include "display/buttons/speedButton.hpp"
#include "display/widgets/widget.hpp"
#include "logic/gameLogic.hpp"
#include "display/widgets/textWidget.hpp"
#include "display/widgets/containerWidget.hpp"

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
   void dataSync() override;
   const Widget& getSubWidget(unsigned index) const override;
   Iterator end() const override { return Iterator(this, 5); }
private:

   Ui& m_ui;
   sf::RectangleShape m_bar;
   ContainerWidget m_speed_button_container;
   SpeedButton m_speed_pause;
   SpeedButton m_speed_normal;
   SpeedButton m_speed_fast;
   SpeedButton m_speed_veryfast;
   ContainerWidget m_screen_button_container;
   CircleButton m_finance_button;
   CircleButton m_properties_button;
   CircleButton m_loans_button;
   CircleButton m_market_button;
   sf::Font m_font;
   TextWidget m_capital_display;
   TextWidget m_debt_display;
   TextWidget m_net_income_display;
   GameLogic::GameSpeed m_current_speed;
   int m_last_button_id;
};

} // namespace Game
