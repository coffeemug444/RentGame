#pragma once
#include <queue>
#include "gameLogic.hpp"
#include "loan.hpp"
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

IL std::queue<bool> ev_stop_game;
IL std::queue<GameLogic::GameSpeed> ev_gamespeed_changed;
IL std::queue<evLoanMonthlyPayment> ev_loan_monthly_payment_arrears;
IL std::queue<evLoanMonthlyPayment> ev_loan_monthly_payment;


};


} // namespace Game
