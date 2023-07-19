#pragma once
#include "widget.hpp"


namespace Game
{

class ContainerWidget : public Widget
{
public:
   ContainerWidget (Widget* parent, const std::vector<unsigned> sub_widget_ids, Widget::PlacementStyle style = ROW)
   :Widget(style)
   ,m_parent(*parent)
   ,m_sub_widget_ids(sub_widget_ids)
   {}

   Iterator end() const override { return Iterator(this, m_sub_widget_ids.size()); }
   const Widget& getSubWidget(unsigned index) const override { return m_parent.getSubWidget(m_sub_widget_ids[index]); }
   void setSubWidgetIds(const std::vector<unsigned>& sub_widget_ids) { m_sub_widget_ids = sub_widget_ids; }
   void setSize(const sf::Vector2f& container_size) override { Widget::setSize(container_size); }

private:
   Widget& m_parent;
   std::vector<unsigned> m_sub_widget_ids;
};
   
} // namespace Game
