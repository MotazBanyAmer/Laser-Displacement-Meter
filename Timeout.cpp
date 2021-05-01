#include "Timeout.h"

void handleTimeoutCounter()
{
  if (timeoutStartTrigger) //?what should i put here
  {
    currentTime2 = millis();
    timeDuration = currentTime2 - currentTime;
  }
}