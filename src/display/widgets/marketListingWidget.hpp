#pragma once
#include "widget.hpp"

namespace Game
{

class MarketListingWidget : public Widget
{
public:
   MarketListingWidget(unsigned id) : m_id(id) {}
   unsigned getId() const { return m_id; }

   // TODO: fill these out
   void handleClick(int button_id) override {}                  //  <--- THESE NEED TO BE DONE
   sf::Vector2f getSize() const override { return {0,0}; }      //  <--- THESE NEED TO BE DONE
   sf::Vector2f getPosition() const override { return {0,0}; }  //  <--- THESE NEED TO BE DONE
   void setScreenSize(const sf::Vector2u& size) override {};    //  <--- THESE NEED TO BE DONE
   void dataSync() override {}                                  //  <--- THESE NEED TO BE DONE
   void move(const sf::Vector2f& pos) override {};              //  <--- THESE NEED TO BE DONE

private:
   unsigned m_id;
};
   
} // namespace Game
