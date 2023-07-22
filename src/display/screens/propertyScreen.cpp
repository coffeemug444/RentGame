#include "propertyScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"


namespace Game
{

PropertyScreen::PropertyScreen() 
:Screen("Property", CC::property_color)
{
   m_title.setPadding({20,0,0,0});
}

void PropertyScreen::setSubWidgetSize()
{
   auto inner_container_size = m_container_size - m_padding;
   float title_height = 60.f;
   m_title.setSize({inner_container_size.x, title_height});
   inner_container_size.y -= title_height;

   if (m_owned_property_widgets.size() == 0) return;

   float property_widget_y = inner_container_size.y / 8.f; // can have 8 on screen at a time (maybe change this)

   sf::Vector2f property_widget_size{inner_container_size.x, property_widget_y};
   for (auto property_widget_ptr : m_owned_property_widgets)
   {
      property_widget_ptr->setSize(property_widget_size);
   }
}

void PropertyScreen::dataSync() 
{
   bool changed = false;
   for (const auto& property : OD::Player::properties)
   {
      if (not listContainsId(property.getId(), m_owned_property_widgets))
      {
         m_owned_property_widgets.push_back(std::make_shared<OwnedPropertyWidget>(property.getId()));
         changed = true;
      }
   }
   for (int i = 0; i < m_owned_property_widgets.size(); i++)
   {
      if (not listContainsId(m_owned_property_widgets[i]->getId(), OD::Player::properties))
      {
         m_owned_property_widgets.erase(m_owned_property_widgets.begin() + i);
         i--;
         changed = true;
      }
   }

   if (changed) 
   {
      setSubWidgetSize();
      placeSubWidgets();
   }
   Screen::dataSync();
}

} // namespace Game