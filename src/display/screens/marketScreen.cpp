#include "marketScreen.hpp"
#include "display/ui.hpp"
#include "observableData.hpp"

namespace Game
{


MarketScreen::MarketScreen() 
:Screen("Market", CC::market_color) 
{
}


void MarketScreen::setSize(const sf::Vector2f& screen_size)
{
   Screen::setSize(screen_size);
   m_title.setPadding({20,0,0,0});
}

void MarketScreen::setSubWidgetSize()
{
   auto inner_container_size = m_container_size - m_padding;
   float title_height = 60.f;
   m_title.setSize({inner_container_size.x, title_height});
   inner_container_size.y -= title_height;

   if (m_market_listing_widgets.size() == 0) return;

   float listing_widget_y = inner_container_size.y / 5.f; // can have 5 on screen at a time (maybe change this)

   sf::Vector2f listing_widget_size{inner_container_size.x, listing_widget_y};
   for (auto listing_widget_ptr : m_market_listing_widgets)
   {
      listing_widget_ptr->setSize(listing_widget_size);
   }
}

void MarketScreen::dataSync() 
{
   bool changed = false;
   auto listings = OD::market.getListings();
   for (const auto& listing : listings)
   {
      if (not listContainsId(listing.getId(), m_market_listing_widgets))
      {
         m_market_listing_widgets.push_back(std::make_shared<MarketListingWidget>(listing.getId()));
         changed = true;
      }
   }
   for (int i = 0; i < m_market_listing_widgets.size(); i++)
   {
      if (not listContainsId(m_market_listing_widgets[i]->getId(), listings))
      {
         m_market_listing_widgets.erase(m_market_listing_widgets.begin() + i);
         i--;
         changed = true;
      }
   }

   if (changed) 
   {
      setSubWidgetSize();
      placeSubWidgets();
   }
   Screen::dataSync();
}


const Widget& MarketScreen::getSubWidget(unsigned index) const 
{ 
   if (index == 0) return m_title;
   return *(m_market_listing_widgets.at(index-1)); 
}


} // namespace Game