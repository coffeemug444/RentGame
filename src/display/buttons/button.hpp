#pragma once
#include <SFML/Graphics.hpp>
#include "util/util.hpp"
#include "display/widgets/widget.hpp"
#include <functional>

namespace Game
{


class Button : public Widget
{
public:
   Button(std::function<void(void)> callback)
      :m_callback(callback){}
   virtual bool mouseIsOver(sf::Vector2i mouse_pos) const = 0;
   virtual void mouseDown(sf::Vector2i mouse_pos) override { m_pressed = mouseIsOver(mouse_pos); }
   virtual void mouseUp(sf::Vector2i mouse_pos) override;
   virtual Iterator end() const override { return begin(); }
   virtual sf::Cursor::Type getCursorType(sf::Vector2i mouse_pos) const override;

protected:
   std::function<void(void)> m_callback;

   int m_button_id;
   bool m_pressed;
};

} // namespace Game