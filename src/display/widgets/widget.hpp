#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Game
{

class Button;
   
class Widget : public sf::Drawable
{
public:
   Widget();
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   virtual void handleClick(int button_id) = 0;
   virtual sf::Cursor::Type getCursorType(sf::Vector2i mouse_pos) const;
   virtual void mouseDown(sf::Vector2i mouse_pos);
   virtual void mouseUp(sf::Vector2i mouse_pos);
   virtual void uiEvents() {}
   virtual void dataSync() {}
   virtual sf::Vector2f getSize() const = 0;
   virtual sf::Vector2f getPosition() const = 0;
   virtual void setScreenSize(const sf::Vector2u& size);
   void setPosition(const sf::Vector2f& pos);
   virtual void move(const sf::Vector2f& pos);
   virtual std::vector<const Widget*> getSubWidgets() const { return {}; }
   virtual std::vector<Widget*> getSubWidgets() { return {}; }
   virtual std::vector<const Button*> getButtons() const = 0;
protected:
   int m_last_button_id;
};


} // namespace Game
