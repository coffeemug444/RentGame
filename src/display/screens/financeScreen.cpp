#include "financeScreen.hpp"
#include "display/constColors.hpp"

namespace Game
{

FinanceScreen::FinanceScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Finance", CC::finance_color)
{
}

void FinanceScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (not m_active) return;
   Screen::draw(target, states);

}
   
      
} // namespace Game
