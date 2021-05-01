#ifndef __TIMER_CONFIG_H__
#define __TIMER_CONFIG_H__

#include "stdint.h"
// #define maxDuration_Sec 200 //!new, not used
// #define dataFreq_Sec 5 //!new, not used

#define maxDuration_mSec 200000
#define dataFreq_mSec 5000

#define timerFq_1Hz 3036     // preload timer 65536-16MHz/256/1Hz
#define timerFq_1000Hz 65473 // preload timer 65536-16MHz/256/1000Hz

typedef struct _timer_
{
    uint32_t secondCounter;
    uint64_t mSecondCounter;

    uint64_t timeDuration;
    uint64_t currentTime;
    uint64_t currentTime2;

    bool timeSetFlag; //!new, used in code def

} _timer_t;

inline volatile _timer_t CentralTimer{0, 0, 0, 0, 0, 0};

void setupTimer();

#endif