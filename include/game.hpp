#pragma once
#include "SFML/Graphics.hpp"
#include "ui.hpp"

class Game
{
public:
   Game();
   void loop();
private:
   void pollEvents();
   sf::RenderWindow m_window;
   Ui m_ui;
};