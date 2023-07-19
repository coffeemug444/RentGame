#include "marketScreen.hpp"
#include "display/ui.hpp"
#include "observableData.hpp"

namespace Game
{


MarketScreen::MarketScreen(Ui& ui) 
:Screen(ui, "Market", CC::market_color) 
{
}


void MarketScreen::setSize(const sf::Vector2f& screen_size)
{
   Screen::setSize(screen_size);
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

   if (changed) Widget::placeSubWidgets();
   Screen::dataSync();
}


} // namespace Game