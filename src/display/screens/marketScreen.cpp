#include "marketScreen.hpp"
#include "display/ui.hpp"
#include "observableData.hpp"

namespace Game
{


MarketScreen::MarketScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Market", CC::market_color) 
{
   setScreenSize(screen_size);
}


void MarketScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   sf::Vector2f market_listing_widget_origin = {10.f,0.1f*screen_size.y};
   for (int i = 0; i < m_market_listing_widgets.size(); i++)
   {
      auto new_pos = market_listing_widget_origin + i*sf::Vector2f{0,20.f+m_market_listing_widgets[i].getSize().y};
      m_market_listing_widgets[i].setPosition(new_pos);
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
         MarketListingWidget new_widget(listing.getId());
         m_market_listing_widgets.push_back(new_widget);
         changed = true;
      }
   }
   for (int i = 0; i < m_market_listing_widgets.size(); i++)
   {
      if (not listContainsId(m_market_listing_widgets[i].getId(), listings))
      {
         m_market_listing_widgets.erase(m_market_listing_widgets.begin() + i);
         i--;
         changed = true;
      }
   }

   if (changed) setScreenSize(m_screen_size);
   Screen::dataSync();
}


} // namespace Game