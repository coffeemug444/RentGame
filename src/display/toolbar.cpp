#include "toolbar.hpp"
#include "util/util.hpp"
#include "ui.hpp"
#include <string>
#include <tuple>
#include "observableData.hpp"

namespace Game
{

Toolbar::Toolbar(Ui& ui, sf::Vector2u screen_size)
:m_ui(ui)
,m_screen_size(screen_size)
,m_finance_button(*this, &Toolbar::finance_callback)
,m_properties_button(*this, &Toolbar::properties_callback)
,m_loans_button(*this, &Toolbar::loans_callback)
,m_market_button(*this, &Toolbar::market_callback)
{
   setScreenSize(screen_size);

   m_bar.setFillColor(OD::toolbar_color);

   m_finance_button.setFillColor(OD::finance_color);
   m_properties_button.setFillColor(OD::property_color);
   m_loans_button.setFillColor(OD::loan_color);
   m_market_button.setFillColor(OD::market_color);

   m_capital_display.setString(std::to_string(OD::capital));
   m_debt_display.setString(std::to_string(OD::debt));
   m_net_income_display.setString(std::to_string(OD::net_income));

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
   
   float button_radius = screen_size.y*0.05f;
   m_finance_button.setRadius(button_radius);  
   m_properties_button.setRadius(button_radius);
   m_loans_button.setRadius(button_radius);
   m_market_button.setRadius(button_radius);

   auto x_pos = [screen_size](int places_from_right) { 
      return screen_size.x - (1+places_from_right)*screen_size.y*0.1f; 
   };

   m_finance_button.setPosition({x_pos(0),bar_y});
   m_properties_button.setPosition({x_pos(1),bar_y});
   m_loans_button.setPosition({x_pos(2),bar_y});
   m_market_button.setPosition({x_pos(3),bar_y});

   float text_height = bar_height * 0.6f;
   float text_offset = (bar_height - text_height)/2.f;

   m_capital_display.setCharacterSize(text_height);
   m_debt_display.setCharacterSize(text_height);
   m_net_income_display.setCharacterSize(text_height);

   m_capital_display.setPosition({text_offset, bar_y+text_offset});
   m_debt_display.setPosition({text_offset+screen_size.x*0.2f, bar_y+text_offset});
   m_net_income_display.setPosition({text_offset+screen_size.x*0.4f, bar_y+text_offset});

   
}

sf::Cursor::Type Toolbar::getCursorType(sf::Vector2i mouse_pos) const
{
   if (mouse_pos.y < m_bar.getPosition().y) return sf::Cursor::Arrow;

   for (const auto& button : {
      m_finance_button,
      m_properties_button,
      m_loans_button,
      m_market_button
   }){
      if (button.mouseIsOver(mouse_pos)) return sf::Cursor::Hand;
   } 

   return sf::Cursor::Arrow;
}

void Toolbar::mouseDown(sf::Vector2i mouse_pos)
{
   for (auto button : {
      m_finance_button,
      m_properties_button,
      m_loans_button,
      m_market_button
   }){
      if (button.mouseIsOver(mouse_pos)) button.click();
   } 
}

void Toolbar::mouseUp(sf::Vector2i mouse_pos)
{

}

bool Toolbar::mouseIsOver(sf::Vector2i mouse_pos) const
{
   return mouse_pos.y > m_bar.getPosition().y;
}

void Toolbar::finance_callback() { m_ui.selectScreen(FINANCE); }
void Toolbar::properties_callback() { m_ui.selectScreen(PROPERTIES); }
void Toolbar::loans_callback() { m_ui.selectScreen(LOANS); }
void Toolbar::market_callback() { m_ui.selectScreen(MARKET); }

void Toolbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_bar);
   target.draw(m_finance_button);
   target.draw(m_properties_button);
   target.draw(m_loans_button);
   target.draw(m_market_button);
   target.draw(m_capital_display);
   target.draw(m_debt_display);
   target.draw(m_net_income_display);
}

} // namespace Game