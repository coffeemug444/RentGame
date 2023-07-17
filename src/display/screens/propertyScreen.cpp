#include "propertyScreen.hpp"
#include "display/ui.hpp"
#include "display/constColors.hpp"


namespace Game
{

PropertyScreen::PropertyScreen(Ui& ui, sf::Vector2u screen_size) 
:Screen(ui, screen_size, "Property", CC::property_color)
{
   setScreenSize(screen_size);
}


void PropertyScreen::setScreenSize(sf::Vector2u screen_size)
{
   Screen::setScreenSize(screen_size);
   sf::Vector2f market_listing_widget_origin = {10.f,0.1f*screen_size.y};
   for (int i = 0; i < m_owned_property_widgets.size(); i++)
   {
      auto new_pos = market_listing_widget_origin + i*sf::Vector2f{0,20.f+m_owned_property_widgets[i].getSize().y};
      m_owned_property_widgets[i].setPosition(new_pos);
   }
}

void PropertyScreen::dataSync() 
{
   bool changed = false;
   for (const auto& property : OD::Player::properties)
   {
      if (not listContainsId(property.getId(), m_owned_property_widgets))
      {
         OwnedPropertyWidget new_widget(property.getId());
         m_owned_property_widgets.push_back(new_widget);
         changed = true;
      }
   }
   for (int i = 0; i < m_owned_property_widgets.size(); i++)
   {
      if (not listContainsId(m_owned_property_widgets[i].getId(), OD::Player::properties))
      {
         m_owned_property_widgets.erase(m_owned_property_widgets.begin() + i);
         i--;
         changed = true;
      }
   }

   if (changed) setScreenSize(m_screen_size);
   Screen::dataSync();
}

} // namespace Game