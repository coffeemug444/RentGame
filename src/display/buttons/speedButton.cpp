#include "speedButton.hpp"
#include "logic/events/eventInterface.hpp"
#include <iostream>


namespace Game
{

SpeedButton::SpeedButton(GameLogic::GameSpeed type, Widget::Alignment alignment)
:CircleButton([&](){EI::ev_gamespeed_changed.push(m_type);}, alignment)
,m_type(type)
,m_symbol_color(sf::Color::White)
{
   m_play_tri.setPrimitiveType(sf::Triangles);
   m_fast_tris.setPrimitiveType(sf::Triangles);
   m_veryfast_tri.setPrimitiveType(sf::Triangles);
}

void SpeedButton::setRadius(float radius)
{
   CircleButton::setRadius(radius);

   m_play_tri.clear();
   m_fast_tris.clear();
   m_veryfast_tri.clear();

   sf::Vector2f base_pos = m_button_circle.getPosition() + sf::Vector2f{radius,radius};

   m_play_tri.append(sf::Vertex{base_pos + sf::Vector2f{-0.2f*radius,-0.4f*radius}, m_symbol_color });
   m_play_tri.append(sf::Vertex{base_pos + sf::Vector2f{-0.2f*radius, 0.4f*radius}, m_symbol_color });
   m_play_tri.append(sf::Vertex{base_pos + sf::Vector2f{ 0.4f*radius, 0          }, m_symbol_color });

   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{-0.4f*radius,-0.4f*radius}, m_symbol_color });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{-0.4f*radius, 0.4f*radius}, m_symbol_color });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{ 0.2f*radius, 0          }, m_symbol_color });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{ 0          ,-0.4f*radius}, m_symbol_color });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{ 0          , 0.4f*radius}, m_symbol_color });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{ 0.6f*radius, 0          }, m_symbol_color });

   m_veryfast_tri.append(sf::Vertex{base_pos + sf::Vector2f{-0.4f*radius,-0.4f*radius}, m_symbol_color });
   m_veryfast_tri.append(sf::Vertex{base_pos + sf::Vector2f{-0.4f*radius, 0.4f*radius}, m_symbol_color });
   m_veryfast_tri.append(sf::Vertex{base_pos + sf::Vector2f{ 0.2f*radius, 0          }, m_symbol_color });
   m_veryfast_rec.setSize({0.1f*radius, 0.8f*radius});
   m_veryfast_rec.setPosition(base_pos + sf::Vector2f{0.2f*radius, -0.4f*radius});

   m_pause_rec_1.setSize({0.1f*radius, 0.8f*radius});
   m_pause_rec_1.setPosition(base_pos + sf::Vector2f{0.2f*radius, -0.4f*radius});
   m_pause_rec_2.setSize({0.1f*radius, 0.8f*radius});
   m_pause_rec_2.setPosition(base_pos + sf::Vector2f{-0.3f*radius, -0.4f*radius});

}

void SpeedButton::setFillColor(const sf::Color& color) 
{
   auto [h,s,v,a] = RGBAToHSVA(color.toInteger());
   h = (h+180)%360;
   if (s == 0) v = 100 - v;
   sf::Color secondary{HSVAtoRGBA(h,s,v,a)};

   setFillColor(color, secondary);
}

void SpeedButton::move(const sf::Vector2f& pos) 
{ 
   CircleButton::move(pos);
   auto move_vertices = [](sf::VertexArray& va, const sf::Vector2f& pos) {
      for (int i = 0; i < va.getVertexCount(); i++)
         va[i].position += pos;
   };
   m_pause_rec_1.move(pos);
   m_pause_rec_2.move(pos);
   move_vertices(m_play_tri, pos);
   move_vertices(m_fast_tris, pos);
   move_vertices(m_veryfast_tri, pos);
   m_veryfast_rec.move(pos);
}

void SpeedButton::setFillColor(const sf::Color& primary, const sf::Color& secondary)
{
   CircleButton::setFillColor(primary);
   m_symbol_color = secondary;

   if(m_play_tri.getVertexCount() > 0) for (int i = 0; i < 3; i++)
   {
      m_play_tri[i].color = secondary;
      m_veryfast_tri[i].color = secondary;
      m_fast_tris[i].color = secondary;
      m_fast_tris[i+3].color = secondary;
   }

   m_veryfast_rec.setFillColor(secondary);
   m_pause_rec_1.setFillColor(secondary);
   m_pause_rec_2.setFillColor(secondary);

}

void SpeedButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   CircleButton::draw(target, states);
   switch(m_type)
   {
   case GameLogic::PAUSE:
      target.draw(m_pause_rec_1);
      target.draw(m_pause_rec_2);
      break;
   case GameLogic::NORMAL:
      target.draw(m_play_tri);
      break;
   case GameLogic::FAST:
      target.draw(m_fast_tris);
      break;
   case GameLogic::VERYFAST:
      target.draw(m_veryfast_tri);
      target.draw(m_veryfast_rec);
      break;
   }

}

   


} // namespace Game