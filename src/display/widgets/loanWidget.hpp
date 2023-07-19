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
   void setSize(const sf::Vector2f& size) override;
   void move(const sf::Vector2f& pos) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   Iterator end() const override { return Iterator(this, 0); }
private:
   unsigned m_id {};
   sf::Text m_principal;
   sf::Text m_total;
   sf::Text m_next_payment;
   sf::RectangleShape m_background_box;
};



} // namespace Game
