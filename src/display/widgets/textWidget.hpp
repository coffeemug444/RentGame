#pragma once
#include "widget.hpp"
#include "observableData.hpp"


namespace Game
{

class TextWidget : public Widget
{
public:
   TextWidget(const std::string& text = "", Widget::Alignment alignment = {V_CENTER, LEFT})
   :Widget(ROW,alignment)
   ,m_text(text, OD::font)
   {
   }

   Iterator end() const override { return begin(); }
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
      target.draw(m_text);
   }
   void setSize(const sf::Vector2f& container_size) override {
      Widget::setSize(container_size);
      m_text.setPosition(getPosition());

      auto inner_container_size = container_size - m_padding;

      float text_height = inner_container_size.y * 0.6f;
      m_text.setCharacterSize(text_height);
      float text_width = m_text.getGlobalBounds().width;

      float empty_y_space = inner_container_size.y - text_height;
      float empty_x_space = inner_container_size.x - text_width;

      if (m_alignment.vertical == V_CENTER)
         m_text.move({0,empty_y_space/2.f});
      if (m_alignment.vertical == BOTTOM)
         m_text.move({0,empty_y_space});
      if (m_alignment.horizontal == H_CENTER)
         m_text.move({empty_x_space/2.f,0});
      if (m_alignment.horizontal == RIGHT)
         m_text.move({empty_x_space,0});

   }
   void setString(const std::string& text) {
      m_text.setString(text);
      setSize(m_container_size); // incase this widget is right aligned
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
