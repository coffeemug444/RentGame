#pragma once
#include <deque>
#include "gameLogic.hpp"
#include <mutex>

namespace Game
{
class EventInterface;
using EI = EventInterface;

class EventInterface
{
public:
static inline std::mutex gametick_mutex;

static inline std::deque<bool> ev_stop_game;
static inline std::deque<GameLogic::GameSpeed> ev_gamespeed_changed;


};


} // namespace Game
