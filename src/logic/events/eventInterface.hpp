#pragma once
#include <queue>
#include "logic/gameLogic.hpp"
#include "events.hpp"
#include "display/ui.hpp"
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

IL std::queue<evNone> ev_stop_game;
IL std::queue<GameLogic::GameSpeed> ev_gamespeed_changed;
IL std::queue<evTakeLoanStatus> ev_take_loan_status;
IL std::queue<evTakeLoan> ev_take_loan;
IL std::queue<evPurchaseProperty> ev_purchase_property;
IL std::queue<Ui::MainScreen> ev_switch_screen;
IL std::queue<unsigned> ev_change_monitored_property_id;
IL std::queue<evPropertyManagedStatus> ev_set_property_managed_status;

};


} // namespace Game
