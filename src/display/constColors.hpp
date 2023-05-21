#pragma once
#include <SFML/Graphics.hpp>

#ifndef IL
#define IL inline static
#endif

namespace Game
{
struct ConstColors;
using CC = ConstColors;
   
struct ConstColors
{
   IL const sf::Color bank_color                {0xf87575ff};
   IL const sf::Color finance_color             {0x8ac97cff};
   IL const sf::Color loan_color                {0xe3a976ff};
   IL const sf::Color market_color              {0xa760ddff};
   IL const sf::Color property_color            {0x6592c9ff};
   IL const sf::Color individual_property_color {0x7fd4b9ff};
   IL const sf::Color toolbar_color             {0xf2d666ff};
   IL const sf::Color green_primary             {0x40e83aff};
   IL const sf::Color green_secondary           {0x137010ff};

};


}