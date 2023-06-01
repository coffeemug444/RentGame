#pragma once
#include <mutex>
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include "logic/gameLogic.hpp"
#include "logic/loan.hpp"

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

   struct Player
   {
      IL unsigned capital = 0;
      IL unsigned debt = 0;
      IL unsigned net_income = 0;
      IL std::vector<Loan> loans;
   };

   static void init()
   {
      font.loadFromFile("font/Rubik-VariableFont_wght.ttf");
   }
};


}