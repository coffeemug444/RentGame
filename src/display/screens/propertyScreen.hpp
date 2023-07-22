#pragma once
#include "screen.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/widgets/ownedPropertyWidget.hpp"
#include <memory>

/*

This screen displays a list of all owned properties, with links
to manage each one 

*/

namespace Game
{

class PropertyScreen : public Screen
{
public:
   PropertyScreen();
   void dataSync() override;
   const Widget& getSubWidget(unsigned index) const override { 
      if (index == 0) return m_title;
      return *(m_owned_property_widgets.at(index-1)); 
   }
   Iterator end() const override { return Iterator(this, 1+m_owned_property_widgets.size()); }
   void setSubWidgetSize() override;
private:

   std::vector<std::shared_ptr<OwnedPropertyWidget>> m_owned_property_widgets;
};

} // namespace Game