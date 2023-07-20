#include "propertyScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"


namespace Game
{

PropertyScreen::PropertyScreen() 
:Screen("Property", CC::property_color)
{
}


void PropertyScreen::setSize(const sf::Vector2f& screen_size)
{
   Screen::setSize(screen_size);
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