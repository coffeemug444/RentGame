#pragma once
#include <SFML/Graphics.hpp>
#include "util/util.hpp"
#include "display/widgets/widget.hpp"

namespace Game
{


class Button : public sf::Drawable
{
public:
   Button(int button_id)
      :m_button_id(button_id){}
   int getId() const { return m_button_id; }
   virtual bool mouseIsOver(sf::Vector2i mouse_pos) const = 0;
protected:
   Widget* m_callback_class;
   int m_button_id;
};

} // namespace Game