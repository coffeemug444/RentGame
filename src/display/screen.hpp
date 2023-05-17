#include <SFML/Graphics.hpp>

namespace Game
{


class Screen : sf::Drawable
{
public:
   Screen(sf::Vector2u screen_size, sf::Color background_color);
   
   virtual sf::Cursor::Type getCursorType(sf::Vector2u mouse_pos) const = 0;
   virtual void setScreenSize(sf::Vector2u screen_size);

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   
   
protected:
   sf::RectangleShape m_background;
   sf::Vector2u m_screen_size;
   sf::Color m_background_color;
   bool m_active;
};

} // namespace Game
