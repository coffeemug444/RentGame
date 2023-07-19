#pragma once
#include "widget.hpp"
#include "observableData.hpp"


namespace Game
{

class TextWidget : public Widget
{
public:
   TextWidget(const std::string& text = "")
   :m_text(text, OD::font)
   {
   }

   Iterator end() const override { return begin(); }
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
      target.draw(m_text);
   }
   void setSize(const sf::Vector2f& container_size) override {
      Widget::setSize(container_size);
      m_text.setCharacterSize(container_size.y);
   }
   void setString(const std::string& text) {
      m_text.setString(text);
   }

   void setFillColor(const sf::Color& color) {
      m_text.setFillColor(color);
   }

   void move(const sf::Vector2f& pos) override {
      Widget::move(pos);
      m_text.move(pos);
   }

protected:
   sf::Text m_text;

};
   
} // namespace Game
