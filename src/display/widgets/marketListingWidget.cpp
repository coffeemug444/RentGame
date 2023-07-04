#include "marketListingWidget.hpp"

namespace Game
{


void MarketListingWidget::handleClick(int button_id) 
{
   switch (button_id)
   {
   case BUY_PROPERTY:
      // TODO: send event to purchase the property with this ID
      break;
   default:
      break;
   }
}

// TODO: get the total size from top-left to bottom-right
sf::Vector2f MarketListingWidget::getSize() const 
{
   return {0,0}; 
}

// TODO: get the position of the lop-left-most element
sf::Vector2f MarketListingWidget::getPosition() const 
{
   return {0,0}; 
}

// TODO: move around the elements in this widget based on the screen size
void MarketListingWidget::setScreenSize(const sf::Vector2u& size) 
{

}

// TODO: retrieve data for listing with this ID and update the fields
void MarketListingWidget::dataSync() 
{

}

// TODO: move all elements in this widget by `pos`
void MarketListingWidget::move(const sf::Vector2f& pos) 
{

}



   
} // namespace Game
