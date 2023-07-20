#pragma once
#include "widget.hpp"
#include "textWidget.hpp"

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
   const Widget& getSubWidget(unsigned index) const override;
   Iterator end() const override { return Iterator(this, 3); }
private:
   unsigned m_id {};
   TextWidget m_principal;
   TextWidget m_total;
   TextWidget m_next_payment;
   sf::RectangleShape m_background_box;
};



} // namespace Game
