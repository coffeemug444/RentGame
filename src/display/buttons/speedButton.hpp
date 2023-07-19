#pragma once
#include <SFML/Graphics.hpp>
#include "circleButton.hpp"
#include "logic/gameLogic.hpp"

namespace Game
{



class SpeedButton : public CircleButton
{
public:
   SpeedButton(GameLogic::GameSpeed type);

   void setRadius(float radius) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void setFillColor(const sf::Color& color) override;
   void setFillColor(const sf::Color& primary, const sf::Color& secondary);
   void move(const sf::Vector2f& pos) override;

private:
   GameLogic::GameSpeed m_type;
   sf::Color m_symbol_color;

   sf::RectangleShape m_pause_rec_1;
   sf::RectangleShape m_pause_rec_2;

   sf::VertexArray m_play_tri;
   
   sf::VertexArray m_fast_tris;

   sf::RectangleShape m_veryfast_rec;
   sf::VertexArray m_veryfast_tri;
   
};

} // namespace Game