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
   PropertyScreen(Ui& ui);
   void setSize(const sf::Vector2f& screen_size) override;
   void dataSync() override;
   const Widget& getSubWidget(unsigned index) const override { return *(m_owned_property_widgets.at(index)); }
   Iterator end() const override { return Iterator(this, m_owned_property_widgets.size()); }
private:

   std::vector<std::shared_ptr<OwnedPropertyWidget>> m_owned_property_widgets;
};

} // namespace Game