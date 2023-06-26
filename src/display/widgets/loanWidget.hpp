#pragma once
#include "widget.hpp"

namespace Game
{


class LoanWidget : public Widget
{
public:
   LoanWidget(unsigned id);
   unsigned getId() const { return m_id; }
   void dataSync() override;
   void handleClick(int button_id) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
   unsigned m_id {};
   sf::Text m_principal;
   sf::Text m_total;
   sf::Text m_next_payment;
};



} // namespace Game
