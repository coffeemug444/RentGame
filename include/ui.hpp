#pragma once
#include "SFML/Graphics.hpp"

class Game;

class Ui : public sf::Drawable
{
public:
   Ui(Game& game, sf::Vector2u screen_size);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
   Game& m_game;
   sf::Vector2u m_screen_size;
   sf::RectangleShape m_toolbar;
};