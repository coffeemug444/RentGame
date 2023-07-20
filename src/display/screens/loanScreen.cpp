#include "loanScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"
#include <algorithm>
#include "logic/events/eventInterface.hpp"

namespace Game
{

LoanScreen::LoanScreen() 
:Screen("Loans", CC::loan_color) 
,m_title_container(this, {}, COL)
,m_bank_screen_button([&](){EI::ev_switch_screen.push(Ui::BANK);}, {V_CENTER,RIGHT})
{
   m_bank_screen_button.setFillColor(CC::bank_color);
   m_title_container.setPadding({20,0,0,0});
   refreshContainerWidgetIndices();
}

void LoanScreen::setSize(const sf::Vector2f& size)
{
   Screen::setSize(size);

   // TODO: PUT EVERYTHING WHERE IT SHOULD BE (using containerWidgets??)
}

void LoanScreen::setSubWidgetSize()
{
   auto inner_container_size = m_container_size - m_padding;
   float title_height = 60.f;
   m_title_container.setSize({inner_container_size.x, title_height});
   inner_container_size.y -= title_height;

   if (m_loan_widgets.size() == 0) return;

   sf::Vector2f loan_widget_size{inner_container_size.x, inner_container_size.y/m_loan_widgets.size()};
   for (auto loan_widget_ptr : m_loan_widgets)
   {
      loan_widget_ptr->setSize(loan_widget_size);
   }
}

void LoanScreen::refreshContainerWidgetIndices()
{
   m_title_container.setSubWidgetIds({
      (unsigned)m_loan_widgets.size()+1, // title
      (unsigned)m_loan_widgets.size()+2  // bank button
   });
}

const Widget& LoanScreen::getSubWidget(unsigned index) const 
{ 
   if (index == 0) return m_title_container;
   index--;
   if (index < m_loan_widgets.size()) return *(m_loan_widgets.at(index));
   index -= m_loan_widgets.size();
   switch(index) {
   case 0:  return m_title;
   case 1:  return m_bank_screen_button;
   default: return Widget::getSubWidget(index);
   }
}

void LoanScreen::dataSync() 
{
   bool changed = false;
   for (const auto& loan : OD::Player::loans)
   {
      if (not listContainsId(loan.getId(), m_loan_widgets))
      {
         m_loan_widgets.push_back(std::make_shared<LoanWidget>(loan.getId()));
         changed = true;
      }
   }
   for (int i = 0; i < m_loan_widgets.size(); i++)
   {
      if (not listContainsId(m_loan_widgets[i]->getId(), OD::Player::loans))
      {
         m_loan_widgets.erase(m_loan_widgets.begin() + i);
         i--;
         changed = true;
      }
   }
   if (changed) 
   {
      refreshContainerWidgetIndices();
      setSubWidgetSize();
      placeSubWidgets();
   }

   Screen::dataSync();
}

} // namespace Game