#pragma once
#include "SFML/Graphics.hpp"


class Game
{
public:
   Game();
   void loop();
private:
   void pollEvents();
   sf::RenderWindow m_window;
};