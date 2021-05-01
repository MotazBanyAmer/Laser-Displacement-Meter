#include "Timeout.h"
#include "TimerConfig.h"

void handleTimeoutCounter()
{
  if (timeoutStartTrigger) //?what should i put here
  {
    CentralTimer.currentTime2 = millis();
    CentralTimer.timeDuration = CentralTimer.currentTime2 - CentralTimer.currentTime;
  }
}