#include "loanScreen.hpp"
#include "ui.hpp"

namespace Game
{

LoanScreen::LoanScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Loans", OD::loan_color, {&m_bank_screen_button}) 
,m_bank_screen_open(false)
,m_bank_screen_button(*this, BANK)
,m_bank_screen(ui, *this, screen_size)
{
   m_bank_screen_button.setFillColor(OD::bank_color);
   m_bank_screen_button.setRadius(0.05f*screen_size.y);
   setScreenSize(screen_size);
}

sf::Cursor::Type LoanScreen::getCursorType(sf::Vector2i mouse_pos) const 
{
   if (m_bank_screen_open)
   {
      return m_bank_screen.getCursorType(mouse_pos);
   }

   return Screen::getCursorType(mouse_pos);
}

void LoanScreen::mouseDown(sf::Vector2i mouse_pos) 
{
   if (m_bank_screen_open)
   {
      m_bank_screen.mouseDown(mouse_pos);
      return;
   }

   Screen::mouseDown(mouse_pos);
}

void LoanScreen::mouseUp(sf::Vector2i mouse_pos) 
{
   if (m_bank_screen_open)
   {
      m_bank_screen.mouseUp(mouse_pos);
      return;
   }

   Screen::mouseUp(mouse_pos);
}

void LoanScreen::handleClick(int button_id)
{
   switch(button_id)
   {
   case BANK:
      m_bank_screen_open = true;
      m_bank_screen.setActive(true);
      break;
   default: break;
   }
}

void LoanScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   m_bank_screen.setScreenSize(screen_size);
   m_bank_screen_button.setPosition({screen_size.x-2*m_bank_screen_button.getRadius(),0});
}

void LoanScreen::setActive(bool active)
{
   Screen::setActive(active);
   m_bank_screen_open = false;
   m_bank_screen.setActive(false);
}

void LoanScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (not m_active) return;
   
   if (m_bank_screen_open)
   {
      target.draw(m_bank_screen);
      return;
   }

   Screen::draw(target, states);
   target.draw(m_bank_screen_button);
}


} // namespace Game