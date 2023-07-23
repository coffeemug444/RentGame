#include "marketScreen.hpp"
#include "display/ui.hpp"
#include "observableData.hpp"

namespace Game
{


MarketScreen::MarketScreen() 
:Screen("Market", CC::market_color) 
,m_listing_header(this, {}, COL)
,m_price_header("Price")
,m_age_header("Age")
,m_purchase_header("Purchase", {TOP, RIGHT})
{
   refreshContainerWidgetIndices();
}


void MarketScreen::setSize(const sf::Vector2f& screen_size)
{
   Screen::setSize(screen_size);
   m_title.setPadding({20,0,0,0});
   m_listing_header.setPadding({20,20,0,0});
   
}

void MarketScreen::refreshContainerWidgetIndices()
{
   unsigned start = m_market_listing_widgets.size() + 2;
   std::vector<unsigned> ids {
      start,
      start + 1,
      start + 2
   };
   m_listing_header.setSubWidgetIds(ids);
}

void MarketScreen::setSubWidgetSize()
{
   auto inner_container_size = m_container_size - m_padding;
   float title_height = 60.f;
   m_title.setSize({inner_container_size.x, title_height});

   float header_height = 40.f;
   m_listing_header.setSize({inner_container_size.x, header_height});

   inner_container_size.y -= (title_height + header_height);

   if (m_market_listing_widgets.size() == 0) return;
   float listing_widget_y = inner_container_size.y / 6.f;

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
      refreshContainerWidgetIndices();
      setSubWidgetSize();
      placeSubWidgets();
   }
   Screen::dataSync();
}


const Widget& MarketScreen::getSubWidget(unsigned index) const 
{ 
   if (index == 0) return m_title;
   if (index == 1) return m_listing_header;
   index -= 2;
   if (index < m_market_listing_widgets.size())
      return *(m_market_listing_widgets.at(index)); 
   index -= m_market_listing_widgets.size();

   switch (index)
   {
   case 0: return m_price_header;
   case 1: return m_age_header;
   case 2: return m_purchase_header;
   default: return Widget::getSubWidget(index);
   }
}


} // namespace Game