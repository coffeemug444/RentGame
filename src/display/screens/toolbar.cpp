#include "toolbar.hpp"
#include "util/util.hpp"
#include "display/ui.hpp"
#include <string>
#include <tuple>
#include "observableData.hpp"
#include "display/constColors.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{

Toolbar::Toolbar()
:Widget(COL)
,m_speed_button_container(this, {5,6,7,8}, COL)
,m_speed_pause(GameLogic::PAUSE, {V_CENTER, H_CENTER})
,m_speed_normal(GameLogic::NORMAL, {V_CENTER, H_CENTER})
,m_speed_fast(GameLogic::FAST, {V_CENTER, H_CENTER})
,m_speed_veryfast(GameLogic::VERYFAST, {V_CENTER, H_CENTER})
,m_screen_button_container(this, {9,10,11,12}, COL)
,m_finance_button([&](){EI::ev_switch_screen.push(Ui::FINANCE);}, {V_CENTER, H_CENTER})
,m_properties_button([&](){EI::ev_switch_screen.push(Ui::PROPERTIES);}, {V_CENTER, H_CENTER})
,m_loans_button([&](){EI::ev_switch_screen.push(Ui::LOANS);}, {V_CENTER, H_CENTER})
,m_market_button([&](){EI::ev_switch_screen.push(Ui::MARKET);}, {V_CENTER, H_CENTER})
,m_capital_display(std::to_string(OD::Player::capital))
,m_debt_display(std::to_string(OD::Player::debt))
,m_net_income_display(std::to_string(OD::Player::net_income))
,m_current_speed(GameLogic::GameSpeed::PAUSE)
,m_last_button_id(0)
{
   m_bar.setFillColor(CC::toolbar_color);

   m_speed_pause.setFillColor(CC::green_primary, CC::green_secondary);
   m_speed_normal.setFillColor(sf::Color::Black);
   m_speed_fast.setFillColor(sf::Color::Black);
   m_speed_veryfast.setFillColor(sf::Color::Black);

   m_finance_button.setFillColor(CC::finance_color);
   m_properties_button.setFillColor(CC::property_color);
   m_loans_button.setFillColor(CC::loan_color);
   m_market_button.setFillColor(CC::market_color);

   m_capital_display.setFillColor(sf::Color::Green);
   m_debt_display.setFillColor(sf::Color::Red);
   m_net_income_display.setFillColor(sf::Color::Green);

}

void Toolbar::dataSync()
{
   if (OD::current_speed != m_current_speed)
   {
      switch (m_current_speed)
      {
      case GameLogic::GameSpeed::PAUSE: m_speed_pause.setFillColor(sf::Color::Black); break;
      case GameLogic::GameSpeed::NORMAL: m_speed_normal.setFillColor(sf::Color::Black); break;
      case GameLogic::GameSpeed::FAST: m_speed_fast.setFillColor(sf::Color::Black); break;
      case GameLogic::GameSpeed::VERYFAST: m_speed_veryfast.setFillColor(sf::Color::Black); break;
      };
      m_current_speed = OD::current_speed;
      switch (m_current_speed)
      {
      case GameLogic::GameSpeed::PAUSE: m_speed_pause.setFillColor(CC::green_primary, CC::green_secondary); break;
      case GameLogic::GameSpeed::NORMAL: m_speed_normal.setFillColor(CC::green_primary, CC::green_secondary); break;
      case GameLogic::GameSpeed::FAST: m_speed_fast.setFillColor(CC::green_primary, CC::green_secondary); break;
      case GameLogic::GameSpeed::VERYFAST: m_speed_veryfast.setFillColor(CC::green_primary, CC::green_secondary); break;
      }
   }
   m_capital_display.setString(std::to_string(OD::Player::capital));
   m_debt_display.setString(std::to_string(OD::Player::debt));
   m_net_income_display.setString(std::to_string(OD::Player::net_income));
}

void Toolbar::move(const sf::Vector2f& pos)
{
   Widget::move(pos);
   m_bar.move(pos);

   m_finance_button.move(pos);  
   m_properties_button.move(pos);
   m_loans_button.move(pos);
   m_market_button.move(pos);

   m_speed_pause.move(pos);
   m_speed_normal.move(pos);
   m_speed_fast.move(pos);
   m_speed_veryfast.move(pos);

   m_capital_display.move(pos);
   m_debt_display.move(pos);
   m_net_income_display.move(pos);
}

void Toolbar::setSize(const sf::Vector2f& size)
{
   Widget::setSize(size);
   m_bar.setSize(size);
}

bool Toolbar::mouseIsOver(sf::Vector2i mouse_pos) const
{
   return mouse_pos.y > m_bar.getPosition().y;
}

const Widget& Toolbar::getSubWidget(unsigned index) const 
{
   switch (index)
   {
   case 0:  return m_speed_button_container;
   case 1:  return m_capital_display;
   case 2:  return m_debt_display;
   case 3:  return m_net_income_display;
   case 4:  return m_screen_button_container;
   case 5:  return m_speed_pause;
   case 6:  return m_speed_normal;
   case 7:  return m_speed_fast;
   case 8:  return m_speed_veryfast;
   case 9: return m_market_button;
   case 10: return m_properties_button;
   case 11: return m_loans_button;
   case 12:  return m_finance_button;
   default: return Widget::getSubWidget(index);
   }
}

void Toolbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_bar);
   target.draw(m_capital_display);
   target.draw(m_debt_display);
   target.draw(m_net_income_display);
   Widget::draw(target, states);
}

} // namespace Game