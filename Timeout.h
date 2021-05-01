#ifndef __TIMEOUT_H__
#define __TIMEOUT_H__

#include "Arduino.h"
//timeout variables
inline boolean timeoutStartTrigger = 0;
#define startTimeout timeoutStartTrigger = 1 //command to trigger the timer on
#define endTimeout timeoutStartTrigger = 0   //command to stop the timer

void handleTimeoutCounter();

#endif