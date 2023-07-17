#pragma once
#include "widget.hpp"
#include "logic/property.hpp"
#include "display/buttons/circleButton.hpp"

namespace Game
{

class OwnedPropertyWidget : public Widget
{
public:
   OwnedPropertyWidget(unsigned id);
   unsigned getId() const { return m_id; }

   void handleClick(int button_id) override;
   sf::Vector2f getSize() const override;
   sf::Vector2f getPosition() const override;
   void setScreenSize(const sf::Vector2u& size) override;
   void dataSync() override;
   void move(const sf::Vector2f& pos) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   std::vector<const Button*> getButtons() const override;
   Iterator end() const override { return Iterator(this, 0); }

private:
   enum ButtonId {
      NONE = 0,
      EDIT_PROPERTY
   };

   unsigned m_id;

   CircleButton m_edit_property_button;
   sf::Text m_price;
   sf::Text m_age;
   sf::RectangleShape m_background_box;
};
   
} // namespace Game
