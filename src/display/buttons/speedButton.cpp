#include "speedButton.hpp"


namespace Game
{


void SpeedButton::setRadius(float radius)
{
   CircleButton::setRadius(radius);

   m_play_tri.clear();
   m_fast_tris.clear();
   m_veryfast_tri.clear();

   sf::Vector2f base_pos = getPosition() + sf::Vector2f{radius,radius};

   m_play_tri.append(sf::Vertex{base_pos + sf::Vector2f{-0.2f*radius,-0.4f*radius} });
   m_play_tri.append(sf::Vertex{base_pos + sf::Vector2f{-0.2f*radius, 0.4f*radius} });
   m_play_tri.append(sf::Vertex{base_pos + sf::Vector2f{ 0.4f*radius, 0          } });

   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{-0.4f*radius,-0.4f*radius} });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{-0.4f*radius, 0.4f*radius} });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{ 0.2f*radius, 0          } });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{ 0          ,-0.4f*radius} });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{ 0          , 0.4f*radius} });
   m_fast_tris.append(sf::Vertex{base_pos + sf::Vector2f{ 0.6f*radius, 0          } });

   m_veryfast_tri.append(sf::Vertex{base_pos + sf::Vector2f{-0.4f*radius,-0.4f*radius} });
   m_veryfast_tri.append(sf::Vertex{base_pos + sf::Vector2f{-0.4f*radius, 0.4f*radius} });
   m_veryfast_tri.append(sf::Vertex{base_pos + sf::Vector2f{ 0.2f*radius, 0          } });
   m_veryfast_rec = sf::RectangleShape{{0.1f*radius, 0.8f*radius}};
   m_veryfast_rec.setPosition(base_pos + sf::Vector2f{0.2f*radius, -0.4f*radius});

   m_pause_rec_1 = sf::RectangleShape{{0.1f*radius, 0.8f*radius}};
   m_pause_rec_1.setPosition(base_pos + sf::Vector2f{0.2f*radius, -0.4f*radius});
   m_pause_rec_2 = sf::RectangleShape{{0.1f*radius, 0.8f*radius}};
   m_pause_rec_2.setPosition(base_pos + sf::Vector2f{-0.3f*radius, -0.4f*radius});

}

void SpeedButton::setPosition(const sf::Vector2f& pos)
{
   CircleButton::setPosition(pos);
   setRadius(getRadius());
}


void SpeedButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   CircleButton::draw(target, states);
   switch(m_type)
   {
   case PAUSE:
      target.draw(m_pause_rec_1);
      target.draw(m_pause_rec_2);
      break;
   case NORMAL:
      target.draw(m_play_tri);
      break;
   case FAST:
      target.draw(m_fast_tris);
      break;
   case VERYFAST:
      target.draw(m_veryfast_tri);
      target.draw(m_veryfast_rec);
      break;
   }

}

   


} // namespace Game