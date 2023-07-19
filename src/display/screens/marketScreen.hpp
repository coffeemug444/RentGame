#pragma once
#include "screen.hpp"
#include "display/constColors.hpp"
#include "display/widgets/marketListingWidget.hpp"
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
   MarketScreen(Ui& ui);
   void setSize(const sf::Vector2f& screen_size) override;
   void dataSync() override;
   const Widget& getSubWidget(unsigned index) const override { return *(m_market_listing_widgets.at(index)); }
   Iterator end() const override { return Iterator(this, m_market_listing_widgets.size()); }
private:

   std::vector<std::shared_ptr<MarketListingWidget>> m_market_listing_widgets;
};

} // namespace Game