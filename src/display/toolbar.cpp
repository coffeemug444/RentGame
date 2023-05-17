#include "toolbar.hpp"
#include "util/util.hpp"
#include <string>

namespace Game
{

Toolbar::Toolbar(Ui& ui, sf::Vector2u screen_size)
:m_ui(ui)
,m_screen_size(screen_size)
{
   setScreenSize(screen_size);

   m_bar.setFillColor(sf::Color{0xf2d666ff});

   m_button.setFillColor(sf::Color::Blue);

   m_capital_display.setString(std::to_string(m_capital));
   m_debt_display.setString(std::to_string(m_debt));
   m_net_income_display.setString(std::to_string(m_net_income));

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
   
   m_button.setRadius(screen_size.y*0.05f);
   m_button.setPosition({screen_size.x - screen_size.y*0.1f,bar_y});

   float text_height = bar_height * 0.6f;
   float text_offset = (bar_height - text_height)/2.f;

   m_capital_display.setCharacterSize(text_height);
   m_debt_display.setCharacterSize(text_height);
   m_net_income_display.setCharacterSize(text_height);

   m_capital_display.setPosition({text_offset, bar_y+text_offset});
   m_debt_display.setPosition({text_offset+screen_size.x*0.2f, bar_y+text_offset});
   m_net_income_display.setPosition({text_offset+screen_size.x*0.4f, bar_y+text_offset});

   
}

sf::Cursor::Type Toolbar::getCursorType(sf::Vector2u mouse_pos) const
{
   if (mouse_pos.y < m_bar.getPosition().y) return sf::Cursor::Arrow;

   auto button_center = m_button.getPosition() 
                      + sf::Vector2f{m_button.getRadius(),
                                     m_button.getRadius()};
   sf::Vector2f d = button_center - mouse_pos;
   if ((d.x*d.x+d.y*d.y) < m_button.getRadius()*m_button.getRadius()) return sf::Cursor::Hand;

   return sf::Cursor::Arrow;
}


void Toolbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_bar);
   target.draw(m_button);
   target.draw(m_capital_display);
   target.draw(m_debt_display);
   target.draw(m_net_income_display);
}

} // namespace Game