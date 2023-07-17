#pragma once
#include "screen.hpp"
#include "display/buttons/circleButton.hpp"
#include "display/widgets/ownedPropertyWidget.hpp"

/*

This screen displays a list of all owned properties, with links
to manage each one 

*/

namespace Game
{

class PropertyScreen : public Screen
{
public:
   PropertyScreen(Ui& ui, sf::Vector2u screen_size);
   void setScreenSize(sf::Vector2u screen_size) override;
   void handleClick(int button_id) override {}
   void dataSync() override;
   std::vector<const Button*> getButtons() const override { return {}; }
   const Widget& getSubWidget(unsigned index) const override { return m_owned_property_widgets.at(index); }
   Iterator end() const override { return Iterator(this, m_owned_property_widgets.size()); }
private:

   std::vector<OwnedPropertyWidget> m_owned_property_widgets;
};

} // namespace Game