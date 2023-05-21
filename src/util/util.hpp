#pragma once
#include "SFML/Graphics.hpp"
#include <tuple>
#include <cmath>

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

std::tuple<int, int, int, int> RGBAToHSVA(sf::Uint32 rgba);

sf::Uint32 HSVAtoRGBA(int hue, int saturation, int value, int alpha);

} // namespace Game
