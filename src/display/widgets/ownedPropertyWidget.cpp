#include "ownedPropertyWidget.hpp"
#include "observableData.hpp"
#include "display/constColors.hpp"
#include "util/util.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{


OwnedPropertyWidget::OwnedPropertyWidget(unsigned id) 
:Widget(COL)
,m_id(id)
,m_edit_property_button([id](){ 
   EI::ev_switch_screen.push(Ui::INDIVIDUAL_PROPERTY);
   EI::ev_change_monitored_property_id.push(id); })
,m_price("Price: ")
,m_age("Age: ")
{
   m_edit_property_button.setFillColor(sf::Color::Red);
   m_background_box.setFillColor(CC::light_grey);
   m_background_box.setOutlineColor(sf::Color::Red);
}

void OwnedPropertyWidget::setSize(const sf::Vector2f& size) 
{
   Widget::setSize(size);
   m_background_box.setSize(size - m_padding);
   m_background_box.setPosition(getPosition());
   m_background_box.move({m_padding.left, m_padding.top});
}

void OwnedPropertyWidget::dataSync() 
{
   auto property_candidate = findById(m_id, OD::Player::properties);
   if (not property_candidate.has_value()) return;
   auto& property = property_candidate.value().get();
   std::string age_string = "Age: ";
   switch (property.getAgeClass())
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
   m_price.setString(std::string("Price: ") + property.getPrice());

   if (property.isManaged())
      m_background_box.setOutlineThickness(0);
   else
      m_background_box.setOutlineThickness(2);
   
   if (property.isRented())
      m_background_box.setFillColor(sf::Color::Green);
   else
      m_background_box.setFillColor(CC::light_grey);
}

const Widget& OwnedPropertyWidget::getSubWidget(unsigned index) const
{
   if (index == 0) return m_age;
   if (index == 1) return m_price;
   if (index == 2) return m_edit_property_button;
   return Widget::getSubWidget(index);
}

void OwnedPropertyWidget::move(const sf::Vector2f& pos) 
{
   Widget::move(pos);
   m_background_box.move(pos);
}

void OwnedPropertyWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_background_box);
   Widget::draw(target, states);
}



} // namespace Game
