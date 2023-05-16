#pragma once
#include "game.hpp"


class Ui : public sf::Drawable
{
public:
   Ui(Game& game);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
   Game& m_game;
};