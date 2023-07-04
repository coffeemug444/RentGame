#pragma once
#include "widget.hpp"
#include "logic/property.hpp"

namespace Game
{

class MarketListingWidget : public Widget
{
public:
   MarketListingWidget(unsigned id);
   unsigned getId() const { return m_id; }

   void handleClick(int button_id) override;
   sf::Vector2f getSize() const override;
   sf::Vector2f getPosition() const override;
   void setScreenSize(const sf::Vector2u& size) override;
   void dataSync() override;
   void move(const sf::Vector2f& pos) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
   enum ButtonId {
      NONE = 0,
      BUY_PROPERTY
   };

   unsigned m_id;

   sf::Text m_price;
   sf::Text m_age;
   sf::RectangleShape m_background_box;
};
   
} // namespace Game
