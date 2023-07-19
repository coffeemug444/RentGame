#pragma once
#include "widget.hpp"
#include "logic/property.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/widgets/textWidget.hpp"

namespace Game
{

class MarketListingWidget : public Widget
{
public:
   MarketListingWidget(unsigned id);
   unsigned getId() const { return m_id; }
   void setSize(const sf::Vector2f& size) override;
   void dataSync() override;
   void move(const sf::Vector2f& pos) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   const Widget& getSubWidget(unsigned index) const override;
   Iterator end() const override { return Iterator(this, 3); }

private:
   enum ButtonId {
      NONE = 0,
      BUY_PROPERTY
   };

   unsigned m_id;

   CircleButton m_purchase_button;
   TextWidget m_price;
   TextWidget m_age;
   sf::RectangleShape m_background_box;
};
   
} // namespace Game
