#include "loanScreen.hpp"
#include "ui.hpp"

namespace Game
{

LoanScreen::LoanScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Loans", sf::Color(OD::loan_color)) 
,m_bank_screen_open(false)
,m_bank_screen(ui, *this, screen_size)
{
}

sf::Cursor::Type LoanScreen::getCursorType(sf::Vector2u mouse_pos) const 
{

   return sf::Cursor::Type::Arrow; 
}

void LoanScreen::mouseDown(sf::Vector2i mouse_pos) 
{
   if (m_bank_screen_open)
   {
      m_bank_screen.mouseDown(mouse_pos);
      return;
   }
}

void LoanScreen::mouseUp(sf::Vector2i mouse_pos) 
{
   if (m_bank_screen_open)
   {
      m_bank_screen.mouseUp(mouse_pos);
      return;
   }
}

void LoanScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (m_bank_screen_open)
   {
      target.draw(m_bank_screen);
      return;
   }

   Screen::draw(target, states);
}


} // namespace Game