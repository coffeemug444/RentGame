#include "ownedPropertyWidget.hpp"
#include "observableData.hpp"
#include "display/constColors.hpp"
#include "util/util.hpp"
#include "logic/events/eventInterface.hpp"

namespace Game
{


OwnedPropertyWidget::OwnedPropertyWidget(unsigned id) 
:m_id(id)
,m_edit_property_button(EDIT_PROPERTY)
,m_price()
,m_age()
{
   const int CHAR_SIZE = 15;

   m_edit_property_button.setFillColor(sf::Color::Red);
   m_edit_property_button.setRadius(20.f);

   m_price.setFont(OD::font);
   m_price.setString("Price: ");
   m_price.setCharacterSize(CHAR_SIZE);
   
   m_age.setFont(OD::font);
   m_age.setString("Age: ");
   m_age.setCharacterSize(CHAR_SIZE);

   m_background_box.setFillColor(CC::light_grey);
   m_background_box.setSize({180.f, 3.f*CHAR_SIZE});
}

std::vector<const Button*> OwnedPropertyWidget::getButtons() const 
{
   return {&m_edit_property_button};
}

void OwnedPropertyWidget::handleClick(int button_id) 
{
   switch (button_id)
   {
   case EDIT_PROPERTY:
      {
         std::lock_guard lock(EI::gametick_mutex);
         EI::ev_switch_screen.push(Ui::MainScreen::INDIVIDUAL_PROPERTY);
         EI::ev_change_monitored_property_id.push(m_id);
      }
      break;
   default:
      break;
   }
}

// TODO: get the total size from top-left to bottom-right
sf::Vector2f OwnedPropertyWidget::getSize() const 
{
   return m_background_box.getSize();
}

// TODO: get the position of the lop-left-most element
sf::Vector2f OwnedPropertyWidget::getPosition() const 
{
   return m_background_box.getPosition();
}

// TODO: move around the elements in this widget based on the screen size
void OwnedPropertyWidget::setScreenSize(const sf::Vector2u& size) 
{
   auto pos = getPosition();
   m_age.setPosition(pos);
   m_price.setPosition(pos);
   m_edit_property_button.setPosition(pos);

   float y = size.y;
   float dy = y * 0.03f;
   m_age.move({5,5});
   m_price.move({5,5 + dy});

   m_edit_property_button.move({100,10});

   float text_height = m_age.getGlobalBounds().height;

   auto box_size = m_background_box.getSize();
   m_background_box.setSize({box_size.x, text_height*2+2.f*dy});
}

// TODO: retrieve data for listing with this ID and update the fields
void OwnedPropertyWidget::dataSync() 
{
   auto property = findById(m_id, OD::Player::properties);
   if (not property.has_value()) return;
   std::string age_string = "Age: ";
   switch (property.value()->getAgeClass())
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
   m_price.setString(std::string("Price: ") + property.value()->getPrice());
}

void OwnedPropertyWidget::move(const sf::Vector2f& pos) 
{
   m_background_box.move(pos);
   m_age.move(pos);
   m_price.move(pos);
   m_edit_property_button.move(pos);
}

void OwnedPropertyWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(m_background_box);
   target.draw(m_age);
   target.draw(m_price);
   Widget::draw(target, states);
}



} // namespace Game
