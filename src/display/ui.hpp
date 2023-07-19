#pragma once
#include "SFML/Graphics.hpp"
#include "screens/toolbar.hpp"
#include "screens/loanScreen.hpp"
#include "screens/financeScreen.hpp"
#include "screens/propertyScreen.hpp"
#include "screens/marketScreen.hpp"
#include "screens/individualPropertyScreen.hpp"
#include "screens/bankScreen.hpp"
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
      MARKET,
      BANK,
      INDIVIDUAL_PROPERTY
   };

   Ui(Game& game, const sf::Vector2u& screen_size);
   void setScreenSize(const sf::Vector2u& screen_size);
   sf::Cursor::Type mouseMoved(sf::Vector2i mouse_pos) const;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void selectScreen(MainScreen screen);
   const Screen& getSelectedScreen() const;
   Screen& getSelectedScreen();
   void mouseDown(sf::Vector2i mouse_pos);
   void mouseUp(sf::Vector2i mouse_pos);   
   void charEntered(char c);
   void backspace();
   void uiEvents();
   void dataSync();

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
   BankScreen m_bank_screen;
   IndividualPropertyScreen m_individual_property_screen;
   sf::Cursor::Type m_current_cursor;
};

} // namespace Game
