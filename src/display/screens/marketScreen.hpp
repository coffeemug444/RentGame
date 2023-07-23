#pragma once
#include "screen.hpp"
#include "display/constColors.hpp"
#include "display/widgets/marketListingWidget.hpp"
#include "display/widgets/containerWidget.hpp"
#include "display/widgets/textWidget.hpp"
#include <memory>

/*

This screen displays a list of all owned properties, with links
to manage each one 

*/

namespace Game
{

class MarketScreen : public Screen
{
public:
   MarketScreen();
   void setSize(const sf::Vector2f& screen_size) override;
   void dataSync() override;
   const Widget& getSubWidget(unsigned index) const override;
   void refreshContainerWidgetIndices() override;
   Iterator end() const override { return Iterator(this, 2+m_market_listing_widgets.size()); }
   void setSubWidgetSize() override;
private:
   ContainerWidget m_listing_header;
   TextWidget m_price_header;
   TextWidget m_age_header;
   TextWidget m_purchase_header;
   std::vector<std::shared_ptr<MarketListingWidget>> m_market_listing_widgets;
};

} // namespace Game