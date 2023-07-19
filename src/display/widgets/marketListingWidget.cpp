#include "marketListingWidget.hpp"
#include "observableData.hpp"
#include "display/constColors.hpp"
#include "util/util.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{


MarketListingWidget::MarketListingWidget(unsigned id) 
:m_id(id)
,m_purchase_button([id](){EI::ev_purchase_listing_id.push(id);})
,m_price()
,m_age()
{
   const int CHAR_SIZE = 15;

   m_purchase_button.setFillColor(sf::Color::Red);
   m_purchase_button.setRadius(20.f);

   m_price.setFont(OD::font);
   m_price.setString("Price: ");
   m_price.setCharacterSize(CHAR_SIZE);
   
   m_age.setFont(OD::font);
   m_age.setString("Age: ");
   m_age.setCharacterSize(CHAR_SIZE);

   m_background_box.setFillColor(CC::light_grey);
   m_background_box.setSize({180.f, 3.f*CHAR_SIZE});
}

void MarketListingWidget::setSize(const sf::Vector2f& size)
{
   auto pos = getPosition();
   m_age.setPosition(pos);
   m_price.setPosition(pos);
   m_purchase_button.setPosition(pos);

   float y = size.y;
   float dy = y * 0.03f;
   m_age.move({5,5});
   m_price.move({5,5 + dy});

   m_purchase_button.move({100,10});

   float text_height = m_age.getGlobalBounds().height;

   auto box_size = m_background_box.getSize();
   m_background_box.setSize({box_size.x, text_height*2+2.f*dy});
}

const Widget& MarketListingWidget::getSubWidget(unsigned index) const 
{
   if (index == 0) return m_purchase_button;
   return Widget::getSubWidget(index);
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
   m_background_box.move(pos);
   m_age.move(pos);
   m_price.move(pos);
   m_purchase_button.move(pos);
}

void MarketListingWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_background_box);
   target.draw(m_age);
   target.draw(m_price);
   Widget::draw(target, states);
}


   
} // namespace Game
