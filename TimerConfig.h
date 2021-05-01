#ifndef __TIMER_CONFIG_H__
#define __TIMER_CONFIG_H__

#include "Arduino.h"

// #define maxDuration_Sec 200 //!new, not used
// #define dataFreq_Sec 5 //!new, not used
unsigned int secondCounter;

#define maxDuration_mSec 200000
#define dataFreq_mSec 5000

volatile unsigned long mSecondCounter;
boolean timeSetFlag = 0;    //!new, used in code def

volatile unsigned long timeDuration = 0;
volatile unsigned long currentTime = 0;
volatile unsigned long currentTime2 = 0;

#define timerFq_1Hz 3036     // preload timer 65536-16MHz/256/1Hz
#define timerFq_1000Hz 65473 // preload timer 65536-16MHz/256/1000Hz

void setupTimer();

#endif