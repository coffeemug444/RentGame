#include "marketListingWidget.hpp"
#include "observableData.hpp"
#include "display/constColors.hpp"
#include "util/util.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{


MarketListingWidget::MarketListingWidget(unsigned id) 
:Widget(COL,{ V_CENTER, LEFT })
,m_id(id)
,m_purchase_button([id](){EI::ev_purchase_listing_id.push(id);}, { V_CENTER, RIGHT })
,m_price("Price: ")
,m_age("Age: ")
{
   setPadding({20,20,20,20});
   m_purchase_button.setFillColor(sf::Color::Red);
   m_purchase_button.setPadding({10,10,10,10});
   m_background_box.setFillColor(CC::light_grey);
}

void MarketListingWidget::setSize(const sf::Vector2f& size)
{
   Widget::setSize(size);
   m_background_box.setSize(size - m_padding);
   m_background_box.setPosition(getPosition());
   m_background_box.move({m_padding.left, m_padding.top});
}

const Widget& MarketListingWidget::getSubWidget(unsigned index) const 
{
   switch(index) {
   case 0: return m_price;
   case 1: return m_age;
   case 2: return m_purchase_button;
   default: return Widget::getSubWidget(index);
   }
}

void MarketListingWidget::dataSync() 
{
   auto listings = OD::market.getListings();
   auto listing = findById(m_id, listings);
   if (not listing.has_value()) return;
   std::string age_string = "Age: ";
   switch (listing.value().get().property.getAgeClass())
   {
   case Property::AgeClass::NEW:
      age_string += "NEW"; break;
   case Property::AgeClass::MID:
      age_string += "MID"; break;
   case Property::AgeClass::OLD:
      age_string += "OLD"; break;
   case Property::AgeClass::VERYOLD:
   default:
      age_string += "VERY OLD"; break;      
   }
   m_age.setString(age_string);
   m_price.setString(std::string("Price: ") + listing.value().get().property.getPrice());
}

void MarketListingWidget::move(const sf::Vector2f& pos) 
{
   Widget::move(pos);
   m_background_box.move(pos);
}

void MarketListingWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_background_box);
   Widget::draw(target, states);
}


   
} // namespace Game
