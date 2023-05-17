#pragma once
#include <mutex>

namespace Game
{
class ObservableData;
using OD = ObservableData;


   
class ObservableData
{
public:
inline static std::mutex data_mutex;
inline static unsigned capital;
inline static unsigned debt;
inline static unsigned net_income;

};


}