#pragma once
#include "SFML/Graphics.hpp"
#include "toolbar.hpp"
#include "loanScreen.hpp"
#include "financeScreen.hpp"
#include "bankScreen.hpp"
#include <mutex>

namespace Game
{

class Game;

class Ui : public sf::Drawable
{
public:
   Ui(Game& game, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size);
   void mouseMoved(sf::Vector2u mouse_pos);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
   Game& m_game;
   sf::Vector2u m_screen_size;
   Toolbar m_toolbar;
   LoanScreen m_loan_screen;
   FinanceScreen m_finance_screen;
   BankScreen m_bank_screen;
   sf::Cursor::Type m_current_cursor;
};

} // namespace Game
