#pragma once
#include "SFML/Graphics.hpp"
#include "toolbar.hpp"
#include "loanScreen.hpp"
#include "financeScreen.hpp"
#include "propertyScreen.hpp"
#include "marketScreen.hpp"
#include <mutex>
#include <map>

namespace Game
{

class Game;



class Ui : public sf::Drawable
{
public:
   enum MainScreen {
      FINANCE,
      PROPERTIES,
      LOANS,
      MARKET
   };

   Ui(Game& game, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size);
   sf::Cursor::Type mouseMoved(sf::Vector2i mouse_pos) const;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void selectScreen(MainScreen screen);
   void mouseDown(sf::Vector2i mouse_pos);
   void mouseUp(sf::Vector2i mouse_pos);

private:
   Game& m_game;
   sf::Vector2u m_screen_size;
   MainScreen m_selected_screen;
   std::map<MainScreen, Screen*> m_screen_map;
   Toolbar m_toolbar;
   LoanScreen m_loan_screen;
   FinanceScreen m_finance_screen;
   PropertyScreen m_property_screen;
   MarketScreen m_market_screen;
   sf::Cursor::Type m_current_cursor;
};

} // namespace Game
