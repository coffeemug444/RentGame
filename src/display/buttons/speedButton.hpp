#pragma once
#include <SFML/Graphics.hpp>
#include "circleButton.hpp"


namespace Game
{



class SpeedButton : public CircleButton
{
public:
   enum SpeedType {
      PAUSE,
      NORMAL,
      FAST,
      VERYFAST
   };

   SpeedButton(ButtonContainer& callback_class, int button_id, SpeedType type)
      :CircleButton(callback_class, button_id)
      ,m_type(type)
      ,m_symbol_color(sf::Color::White)
   {
      m_play_tri.setPrimitiveType(sf::Triangles);
      m_fast_tris.setPrimitiveType(sf::Triangles);
      m_veryfast_tri.setPrimitiveType(sf::Triangles);
   }

   void setRadius(float radius) override;
   void setPosition(const sf::Vector2f& pos) override;
   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   void setFillColor(const sf::Color& color) override;
   void setFillColor(const sf::Color& primary, const sf::Color& secondary);

private:
   SpeedType m_type;
   sf::Color m_symbol_color;

   sf::RectangleShape m_pause_rec_1;
   sf::RectangleShape m_pause_rec_2;

   sf::VertexArray m_play_tri;
   
   sf::VertexArray m_fast_tris;

   sf::RectangleShape m_veryfast_rec;
   sf::VertexArray m_veryfast_tri;
   
};

} // namespace Game