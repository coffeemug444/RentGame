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

Toolbar::Toolbar(Ui& ui, sf::Vector2u screen_size)
:Widget({ &m_finance_button
                  ,&m_properties_button
                  ,&m_loans_button
                  ,&m_market_button
                  ,&m_speed_pause
                  ,&m_speed_normal
                  ,&m_speed_fast
                  ,&m_speed_veryfast})
,m_ui(ui)
,m_screen_size(screen_size)
,m_speed_pause(*this, PAUSE, SpeedButton::PAUSE)
,m_speed_normal(*this, NORMAL, SpeedButton::NORMAL)
,m_speed_fast(*this, FAST, SpeedButton::FAST)
,m_speed_veryfast(*this, VERYFAST, SpeedButton::VERYFAST)
,m_finance_button(*this, FINANCE)
,m_properties_button(*this, PROPERTIES)
,m_loans_button(*this, LOANS)
,m_market_button(*this, MARKET)
,m_current_speed(GameLogic::GameSpeed::PAUSE)
,m_last_button_id(0)
{
   setScreenSize(screen_size);

   m_bar.setFillColor(CC::toolbar_color);


   m_speed_pause.setFillColor(CC::green_primary, CC::green_secondary);
   m_speed_normal.setFillColor(sf::Color::Black);
   m_speed_fast.setFillColor(sf::Color::Black);
   m_speed_veryfast.setFillColor(sf::Color::Black);

   m_finance_button.setFillColor(CC::finance_color);
   m_properties_button.setFillColor(CC::property_color);
   m_loans_button.setFillColor(CC::loan_color);
   m_market_button.setFillColor(CC::market_color);

   m_capital_display.setString(std::to_string(OD::Player::capital));
   m_debt_display.setString(std::to_string(OD::Player::debt));
   m_net_income_display.setString(std::to_string(OD::Player::net_income));

   m_font.loadFromFile("font/Rubik-VariableFont_wght.ttf");

   m_capital_display.setFont(m_font);
   m_debt_display.setFont(m_font);
   m_net_income_display.setFont(m_font);

   m_capital_display.setFillColor(sf::Color::Green);
   m_debt_display.setFillColor(sf::Color::Red);
   m_net_income_display.setFillColor(sf::Color::Green);

}

void Toolbar::setScreenSize(sf::Vector2u screen_size)
{
   m_screen_size = screen_size;

   float bar_y = screen_size.y*0.9f;
   float bar_height = screen_size.y*0.1f;

   m_bar.setSize({static_cast<float>(screen_size.x), bar_height});
   m_bar.setPosition({0,bar_y});
   
   float button_radius = screen_size.y*0.025f;
   m_finance_button.setRadius(button_radius);  
   m_properties_button.setRadius(button_radius);
   m_loans_button.setRadius(button_radius);
   m_market_button.setRadius(button_radius);

   m_speed_pause.setRadius(button_radius);
   m_speed_normal.setRadius(button_radius);
   m_speed_fast.setRadius(button_radius);
   m_speed_veryfast.setRadius(button_radius);

   // 5% width per page button (+5% padding) = 25%
   // 5% width per time button (+5% padding) = 25%
   // leaves 50% for text

   auto x_pos = [screen_size,button_radius](int places_from_right) { 
      return screen_size.x - (1.5f+places_from_right)*2*button_radius; 
   };

   m_finance_button.setPosition({x_pos(0),bar_y+button_radius});
   m_properties_button.setPosition({x_pos(1),bar_y+button_radius});
   m_loans_button.setPosition({x_pos(2),bar_y+button_radius});
   m_market_button.setPosition({x_pos(3),bar_y+button_radius});

   m_speed_pause.setPosition({(0.5f + 0)*2*button_radius, bar_y+button_radius});
   m_speed_normal.setPosition({(0.5f + 1)*2*button_radius, bar_y+button_radius});
   m_speed_fast.setPosition({(0.5f + 2)*2*button_radius, bar_y+button_radius});
   m_speed_veryfast.setPosition({(0.5f + 3)*2*button_radius, bar_y+button_radius});

   float text_height = bar_height * 0.6f;
   float text_offset_y = bar_y+(bar_height - text_height)/2.f;
   float text_offset_x = 10*button_radius;
   float text_w = (static_cast<float>(screen_size.x) - 20*button_radius) / 3.f;

   m_capital_display.setCharacterSize(text_height);
   m_debt_display.setCharacterSize(text_height);
   m_net_income_display.setCharacterSize(text_height);

   m_capital_display.setPosition({text_offset_x, text_offset_y});
   m_debt_display.setPosition({text_offset_x + text_w, text_offset_y});
   m_net_income_display.setPosition({text_offset_x + 2*text_w, text_offset_y});

   
}

bool Toolbar::mouseIsOver(sf::Vector2i mouse_pos) const
{
   return mouse_pos.y > m_bar.getPosition().y;
}

sf::Vector2f Toolbar::getSize() const
{
   return m_bar.getSize();
}

sf::Vector2f Toolbar::getPosition() const
{
   return m_bar.getPosition();
}

void Toolbar::handleClick(int button_id)
{
   switch(button_id)
   {
      case FINANCE: m_ui.selectScreen(Ui::FINANCE); break;
      case PROPERTIES: m_ui.selectScreen(Ui::PROPERTIES); break;
      case LOANS: m_ui.selectScreen(Ui::LOANS); break;
      case MARKET: m_ui.selectScreen(Ui::MARKET); break;
      case PAUSE: {std::lock_guard lock(EI::gametick_mutex);
         EI::ev_gamespeed_changed.push(GameLogic::PAUSE); break;}
      case NORMAL: {std::lock_guard lock(EI::gametick_mutex);
         EI::ev_gamespeed_changed.push(GameLogic::NORMAL); break;}
      case FAST: {std::lock_guard lock(EI::gametick_mutex);
         EI::ev_gamespeed_changed.push(GameLogic::FAST); break;}
      case VERYFAST: {std::lock_guard lock(EI::gametick_mutex);
         EI::ev_gamespeed_changed.push(GameLogic::VERYFAST); break;}
   }
}

void Toolbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
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


   target.draw(m_bar);
   for (auto button_ptr : m_buttons)
   {
      target.draw(*button_ptr);
   }
   target.draw(m_capital_display);
   target.draw(m_debt_display);
   target.draw(m_net_income_display);
}

} // namespace Game