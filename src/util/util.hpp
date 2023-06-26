#pragma once
#include "SFML/Graphics.hpp"
#include <tuple>
#include <cmath>
#include <queue>
#include <algorithm>
#include <optional>

namespace Game
{

template <typename T>
concept hasId = requires (T t)
{
   { t.getId() } -> std::same_as<unsigned>;
};

template<typename T>
void clear(std::queue<T>& q)
{
   std::queue<T> empty;
   std::swap( q, empty );
}

template <typename T>
requires hasId<T>
bool listContainsId(unsigned id, std::vector<T>& v)
{
   auto it = std::ranges::find_if(v, [id](T t){ return id == t.getId(); });
   return it != v.end();
}

template <typename T>
requires hasId<T>
std::optional<T*> findById(unsigned id, std::vector<T>& v)
{
   auto it = std::ranges::find_if(v, [id](T t){ return id == t.getId(); });
   if (it == v.end()) return {};
   return &(*it);
}

template <typename T>
requires hasId<T>
bool deleteById(unsigned id, std::vector<T>& v)
{
   auto it = std::ranges::find_if(v, [id](T t){ return id == t.getId(); });
   if (it == v.end()) return false;
   v.erase(it);
   return true;
}

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
