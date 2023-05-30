#pragma once
#include <SFML/Graphics.hpp>
#include "display/buttons/buttonContainer.hpp"

namespace Game
{

class Screen;

class Widget : public ButtonContainer, public sf::Drawable
{
public:
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void handleClick(int button_id) override {};
};



} // namespace Game
