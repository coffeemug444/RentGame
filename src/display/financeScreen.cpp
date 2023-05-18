#include "financeScreen.hpp"

namespace Game
{

FinanceScreen::FinanceScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Finance", sf::Color(0x8ac97cff))
,m_bank_screen(ui, screen_size) 
{
}

void FinanceScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (not m_active) return;
   Screen::draw(target, states);

   target.draw(m_bank_screen);
}
   
      
} // namespace Game
