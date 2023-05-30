#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Game
{

class Button;
   
class Widget : public sf::Drawable
{
public:
   Widget(const std::vector<Button*>& buttons = {}, const std::vector<Widget*>& sub_containers = {});
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   virtual void handleClick(int button_id) = 0;
   virtual sf::Cursor::Type getCursorType(sf::Vector2i mouse_pos) const;
   virtual void mouseDown(sf::Vector2i mouse_pos);
   virtual void mouseUp(sf::Vector2i mouse_pos);
protected:
   std::vector<Button*> m_buttons;
   std::vector<Widget*> m_sub_containers;
   int m_last_button_id;
};


} // namespace Game
