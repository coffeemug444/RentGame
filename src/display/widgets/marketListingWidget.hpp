#pragma once
#include "widget.hpp"

namespace Game
{

class MarketListingWidget : public Widget
{
public:
   MarketListingWidget(unsigned id) : m_id(id) {}
   unsigned getId() const { return m_id; }

   void handleClick(int button_id) override;
   sf::Vector2f getSize() const override;
   sf::Vector2f getPosition() const override;
   void setScreenSize(const sf::Vector2u& size) override;
   void dataSync() override;
   void move(const sf::Vector2f& pos) override;

private:
   unsigned m_id;
   enum ButtonId {
      NONE = 0,
      BUY_PROPERTY
   };
};
   
} // namespace Game
