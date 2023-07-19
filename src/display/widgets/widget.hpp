#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Game
{
   
class Widget : public sf::Drawable
{
public:
   enum PlacementStyle {
      ROW,     // elements are placed top to bottom
      COL      // elements are placed left to right
   };
   enum VerticalAlignment {
      TOP,
      BOTTOM,
      V_CENTER
   };
   enum HorizontalAlignment {
      LEFT,
      RIGHT,
      H_CENTER
   };
   struct Alignment {
      VerticalAlignment vertical;
      HorizontalAlignment horizontal;
   };
   Widget(PlacementStyle style = ROW, Alignment alignment = { TOP, LEFT }) 
   :m_placement_style(style) 
   ,m_alignment(alignment)
   {} 

   class Iterator {
   public:
      Iterator(const Widget* base, unsigned index): m_base(base), m_index(index) {}
      void operator++() { m_index++; }
      void operator--() { if (m_index > 0) m_index--; }
      unsigned operator-(const Iterator& other) { return m_index - other.m_index; }
      Widget& operator*() { return m_base->_getSubWidget(m_index); }
      bool operator!=(const Iterator& other) const {
         return m_base != other.m_base || m_index != other.m_index;
      }
   private:
      const Widget* m_base;
      unsigned m_index;
   };

   virtual const Widget& getSubWidget(unsigned index) const { return *this; }
   Widget& getSubWidget(unsigned index) { return _getSubWidget(index); }
   
   Iterator begin() const { return Iterator(this, 0); }
   virtual Iterator end() const = 0;

   // no copying allowed. This makes it VERY difficult for widgets to maintain
   // a pointer to their parent
   Widget(const Widget& other) = delete; 

   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   virtual sf::Cursor::Type getCursorType(sf::Vector2i mouse_pos) const;
   virtual void mouseDown(sf::Vector2i mouse_pos);
   virtual void mouseUp(sf::Vector2i mouse_pos);
   virtual void uiEvents();
   virtual void dataSync();
   virtual void charEntered(char c);
   virtual void backspace();
   virtual sf::Vector2f getSize() const { return m_container_size; }
   sf::Vector2f getPosition() const { return m_position; }
   virtual void setSize(const sf::Vector2f& container_size) = 0;
   virtual void setSubWidgetSize();
   void placeSubWidgets();
   void setPosition(const sf::Vector2f& pos);
   virtual void move(const sf::Vector2f& pos);
protected:
   PlacementStyle m_placement_style;
   Alignment m_alignment;
   sf::Vector2f m_container_size;
   sf::Vector2f m_position;
private:
   Widget& _getSubWidget(unsigned index) const { return const_cast<Widget&>(getSubWidget(index)); }
};


} // namespace Game
