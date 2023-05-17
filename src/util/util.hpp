#pragma once
#include "SFML/Graphics.hpp"

namespace Game
{


template<typename A, typename B>
requires std::is_arithmetic_v<A> && std::is_arithmetic_v<B>
auto operator* (const sf::Vector2<A>& l, const sf::Vector2<B>& r) 
-> sf::Vector2<decltype(l.x*r.x)>
{
   return {l.x*r.x,l.y*r.y};
}

template<typename A, typename B>
requires std::is_arithmetic_v<A> && std::is_arithmetic_v<B>
auto operator/ (const sf::Vector2<A>& l, const sf::Vector2<B>& r) 
-> sf::Vector2<decltype(l.x/r.x)>
{
   return {l.x/r.x,l.y/r.y};
}

template<typename A, typename B>
requires std::is_arithmetic_v<A> && std::is_arithmetic_v<B>
auto operator+ (const sf::Vector2<A>& l, const sf::Vector2<B>& r) 
-> sf::Vector2<decltype(l.x+r.x)>
{
   return {l.x+r.x,l.y+r.y};
}

template<typename A, typename B>
requires std::is_arithmetic_v<A> && std::is_arithmetic_v<B>
auto operator- (const sf::Vector2<A>& l, const sf::Vector2<B>& r) 
-> sf::Vector2<decltype(l.x-r.x)>
{
   return {l.x-r.x,l.y-r.y};
}

} // namespace Game
