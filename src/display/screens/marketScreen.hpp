#pragma once
#include "screen.hpp"
#include "display/constColors.hpp"
#include "display/widgets/marketListingWidget.hpp"

/*

This screen displays a list of all owned properties, with links
to manage each one 

*/

namespace Game
{

class MarketScreen : public Screen
{
public:
   MarketScreen(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size) override;
   void handleClick(int button_id) override {}
   void dataSync() override;
   std::vector<const Button*> getButtons() const override { return {}; }
   const Widget& getSubWidget(unsigned index) const override { return m_market_listing_widgets.at(index); }
   Iterator end() const override { return Iterator(this, m_market_listing_widgets.size()); }
private:

   std::vector<MarketListingWidget> m_market_listing_widgets;
};

} // namespace Game