#include "financeScreen.hpp"
#include "observableData.hpp"

namespace Game
{

FinanceScreen::FinanceScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Finance", sf::Color(OD::finance_color))
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
