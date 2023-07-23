#include "propertyScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"


namespace Game
{

PropertyScreen::PropertyScreen() 
:Screen("Property", CC::property_color)
,m_property_header(this, {}, COL)
,m_price_header("Price")
,m_age_header("Age")
,m_edit_header("Edit", { TOP, RIGHT })
{
   m_title.setPadding({20,0,0,0});
   m_property_header.setPadding({20,20,0,0});
   refreshContainerWidgetIndices();
}

void PropertyScreen::refreshContainerWidgetIndices()
{
   unsigned start = m_owned_property_widgets.size() + 2;
   std::vector<unsigned> ids {
      start,
      start + 1,
      start + 2
   };
   m_property_header.setSubWidgetIds(ids);
}

void PropertyScreen::setSubWidgetSize()
{
   auto inner_container_size = m_container_size - m_padding;
   float title_height = 60.f;
   m_title.setSize({inner_container_size.x, title_height});

   float header_height = 40.f;
   m_property_header.setSize({inner_container_size.x, header_height});

   inner_container_size.y -= (title_height + header_height);
   if (m_owned_property_widgets.size() == 0) return;

   float property_widget_y = inner_container_size.y / 6.f;

   sf::Vector2f property_widget_size{inner_container_size.x, property_widget_y};
   for (auto property_widget_ptr : m_owned_property_widgets)
   {
      property_widget_ptr->setSize(property_widget_size);
   }
}

const Widget& PropertyScreen::getSubWidget(unsigned index) const { 
   if (index == 0) return m_title;
   if (index == 1) return m_property_header;
   index -= 2;
   if (index < m_owned_property_widgets.size())
      return *(m_owned_property_widgets.at(index)); 
   index -= m_owned_property_widgets.size();
   switch (index)
   {
   case 0: return m_price_header;
   case 1: return m_age_header;
   case 2: return m_edit_header;
   default: return Widget::getSubWidget(index);
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
      refreshContainerWidgetIndices();
      setSubWidgetSize();
      placeSubWidgets();
   }
   Screen::dataSync();
}

} // namespace Game