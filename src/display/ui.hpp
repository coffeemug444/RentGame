#pragma once
#include "SFML/Graphics.hpp"
#include "toolbar.hpp"
#include <mutex>

namespace Game
{

class Game;

class Ui : public sf::Drawable
{
public:
   Ui(Game& game, sf::Vector2u screen_size);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
   Game& m_game;
   mutable std::mutex m_data_mutex;
   sf::Vector2u m_screen_size;
   Toolbar m_toolbar;
};

} // namespace Game
