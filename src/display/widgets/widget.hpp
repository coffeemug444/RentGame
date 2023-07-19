#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Game
{
   
class Widget : public sf::Drawable
{
public:
   Widget();

   class Iterator {
   public:
      Iterator(const Widget* base, unsigned index): m_base(base), m_index(index) {}
      void operator++() { m_index++; }
      void operator--() { if (m_index > 0) m_index--; }
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
   virtual sf::Vector2f getSize() const = 0;
   virtual sf::Vector2f getPosition() const = 0;
   virtual void setScreenSize(const sf::Vector2u& size);
   void setPosition(const sf::Vector2f& pos);
   virtual void move(const sf::Vector2f& pos);
private:
   Widget& _getSubWidget(unsigned index) const { return const_cast<Widget&>(getSubWidget(index)); }
};


} // namespace Game
