#pragma once
#include "screen.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/widgets/ownedPropertyWidget.hpp"
#include "display/widgets/containerWidget.hpp"
#include "display/widgets/textWidget.hpp"
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
   const Widget& getSubWidget(unsigned index) const override;
   Iterator end() const override { return Iterator(this, 2+m_owned_property_widgets.size()); }
   void refreshContainerWidgetIndices() override;
   void setSubWidgetSize() override;
private:
   ContainerWidget m_property_header;
   TextWidget m_price_header;
   TextWidget m_age_header;
   TextWidget m_edit_header;
   std::vector<std::shared_ptr<OwnedPropertyWidget>> m_owned_property_widgets;
};

} // namespace Game