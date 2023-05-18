#pragma once
#include <mutex>
#include <stdint.h>

namespace Game
{
class ObservableData;
using OD = ObservableData;


   
class ObservableData
{
public:
inline static std::mutex data_mutex;

inline static const uint32_t bank_color = 0xe3c23dff;
inline static const uint32_t finance_color = 0x8ac97cff;
inline static const uint32_t loan_color = 0xe3c23dff;
inline static const uint32_t market_color = 0x6775f3ff;
inline static const uint32_t property_color = 0x6592c9ff;
inline static const uint32_t toolbar_color = 0xf2d666ff;

inline static unsigned capital;
inline static unsigned debt;
inline static unsigned net_income;

};


}