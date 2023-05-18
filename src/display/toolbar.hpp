#pragma once
#include <SFML/Graphics.hpp>
#include <tuple>
#include "button.hpp"

namespace Game
{

class Ui;

enum ToolbarScreen
{
   FINANCE,
   PROPERTIES,
   LOANS,
   MARKET
};
   
class Toolbar : public sf::Drawable
{
public:
   Toolbar(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size);
   std::tuple<bool, sf::Cursor::Type> getCursorType(sf::Vector2i mouse_pos) const;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void mouseDown(sf::Vector2i mouse_pos);
   void mouseUp(sf::Vector2i mouse_pos);
private:
   void finance_callback();
   void properties_callback();
   void loans_callback();
   void market_callback();
   Ui& m_ui;
   sf::Vector2u m_screen_size;
   sf::RectangleShape m_bar;
   Button<Toolbar> m_finance_button;
   Button<Toolbar> m_properties_button;
   Button<Toolbar> m_loans_button;
   Button<Toolbar> m_market_button;
   sf::Font m_font;
   sf::Text m_capital_display;
   sf::Text m_debt_display;
   sf::Text m_net_income_display;
};

} // namespace Game
