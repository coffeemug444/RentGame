#pragma once
#include <deque>
#include "gameLogic.hpp"
#include <mutex>

#ifndef IL
#define IL inline static
#endif

namespace Game
{
struct EventInterface;
using EI = EventInterface;

struct EventInterface
{
IL std::mutex gametick_mutex;

IL std::deque<bool> ev_stop_game;
IL std::deque<GameLogic::GameSpeed> ev_gamespeed_changed;


};


} // namespace Game
