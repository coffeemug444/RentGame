#pragma once
#include <mutex>
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include "logic/gameLogic.hpp"

namespace Game
{
class ObservableData;
using OD = ObservableData;


   
class ObservableData
{
public:
inline static std::mutex data_mutex;

inline static const sf::Color bank_color                {0xf87575ff};
inline static const sf::Color finance_color             {0x8ac97cff};
inline static const sf::Color loan_color                {0xe3a976ff};
inline static const sf::Color market_color              {0xa760ddff};
inline static const sf::Color property_color            {0x6592c9ff};
inline static const sf::Color individual_property_color {0x7fd4b9ff};
inline static const sf::Color toolbar_color             {0xf2d666ff};
inline static const sf::Color green_primary             {0x40e83aff};
inline static const sf::Color green_secondary           {0x137010ff};

inline static GameLogic::GameSpeed current_speed  {GameLogic::GameSpeed::PAUSE};

inline static unsigned capital;
inline static unsigned debt;
inline static unsigned net_income;

};


}