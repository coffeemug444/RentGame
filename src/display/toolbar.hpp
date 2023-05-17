#pragma once
#include <SFML/Graphics.hpp>

namespace Game
{

class Ui;
   
class Toolbar : public sf::Drawable
{
public:
   Toolbar(Ui& ui, sf::Vector2u screen_size);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
   Ui& m_ui;
   sf::Vector2u m_screen_size;
   sf::RectangleShape m_bar;
};

} // namespace Game
