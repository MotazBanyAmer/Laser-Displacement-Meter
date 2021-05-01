#include "TimerConfig.h"
#include "Arduino.h"

void setupTimer()
{
  //  **Inturrubts**
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  //TCNT1 = timerFq_1Hz;
  TCNT1 = timerFq_1000Hz;
  TCCR1B |= (1 << CS12);
  //TCCR1B |= (1 << CS10);    // 1024 prescaler
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  interrupts();           // enable all interrupts
  //*****
}

