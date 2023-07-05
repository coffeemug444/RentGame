#pragma once
#include <mutex>
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include "logic/gameLogic.hpp"
#include "logic/loan.hpp"
#include "logic/property.hpp"
#include "logic/market.hpp"

#ifndef IL
#define IL inline static
#endif

namespace Game
{
struct ObservableData;
using OD = ObservableData;


struct ObservableData
{
   IL std::mutex data_mutex;

   IL sf::Font font;

   IL bool game_running = true;
   IL GameLogic::GameSpeed current_speed  {GameLogic::GameSpeed::PAUSE};

   struct Date
   {
      IL const unsigned WEEK_LEN = 7; // 7 days
      IL const unsigned MONTH_LEN = 4 * WEEK_LEN; // 4*7 = 28 days
      IL const unsigned YEAR_LEN = 12 * MONTH_LEN; // 12*28 = 336 days
      IL unsigned day = 0;
      IL unsigned getDayOfMonth() { return day % MONTH_LEN; }
      IL unsigned getWeekday() { return day % WEEK_LEN; }
      IL unsigned getMonth() { return (day % YEAR_LEN) / MONTH_LEN; }
      IL unsigned getYear() { return day / YEAR_LEN; }
   };

   struct Player
   {
      IL unsigned capital = 0;
      IL unsigned debt = 0;
      IL unsigned net_income = 0;
      IL std::vector<Loan> loans;
      IL std::vector<Property> properties;
   };

   IL unsigned monitored_property_id = 0;

   IL Market market;

   static void init()
   {
      font.loadFromFile("font/Rubik-VariableFont_wght.ttf");
   }
};


}