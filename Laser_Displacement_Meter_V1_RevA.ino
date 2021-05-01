#include "B707C.h"
#include "TimerConfig.h"
#include "Timeout.h"
#include "Central.h"

B707C Laser;

ISR(TIMER1_OVF_vect);

void setup()
{
    initProject(); //Initialize project
    startup_actions();

    //Laser.laserOn();
}

void loop()
{
    Laser.demandData(static_cast<char>(B707C_dModes::SlowMode));
    Laser.waitResp_Dist();
    // delay(1000);
    Serial.println(Laser.getDistance());
}

ISR(TIMER1_OVF_vect) // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  TCNT1 = 3036; // preload timer
  mSecondCounter++;
  handleTimeoutCounter();
  if (mSecondCounter % 1000 == 0)
    secondCounter++;

  /*
    if (startTimeoutFlag) {
      timeoutCounter++;
      if (timeoutCounter % timeoutDuration == 0) {
        timeoutErrorFlag = 1;
      }
      if (timeoutCounter >= maxDuration) timeoutCounter = 0;
    }
    if (startErrorRepeatFlag)
    {
      errorTimerCounter++;
      if (errorTimerCounter >= maxDuration) timeoutCounter = 0;
    }
  */

  if (mSecondCounter % dataFreq_mSec == 0)
    timeSetFlag = 1;
  if (mSecondCounter >= maxDuration_mSec)
    mSecondCounter = 0;

  if (secondCounter %  == 0)
    timeSetFlag = 1;
  if (secondCounter % dataFreq == 0)
    Upd_Temperature = 1;
  if (secondCounter % dataFreq == 0)
    Upd_Laser = 1;
  if (secondCounter % dataFreq == 0)
    get_Console = 1;
  if (secondCounter % dataFreq == 0)
    get_OpMode = 1;
  if (secondCounter % dataFreq == 0)
    get_ReqTime = 1;
  if (secondCounter >= maxDuration)
    secondCounter = 0;
}
