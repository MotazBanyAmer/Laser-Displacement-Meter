#include "B707C.h"
#include "TimerConfig.h"
#include "Timeout.h"
#include "Central.h"
#include "Errors.h"

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
    if (dataFlag.Upd_Laser)
    {
        Laser.demandData(static_cast<char>(B707C_dModes::SlowMode));
        Laser.waitResp_Dist();
        Serial.println(Laser.getDistance());

        if (Laser.isDone())
        {
            if (!Laser.isThereError()) //*reading success, send the reading
            {
                //SerialDebug.println("Reading Laser -- Slow");
                payload_Data.distance = Laser.getDistance();
                payload_Data.signalQuality = Laser.getSignalQuality();

                SerialDebug.print("Distance : ");
                SerialDebug.println(payload_Data.distance, 3);
                SerialDebug.print("signal Quality : ");
                SerialDebug.println(payload_Data.signalQuality);
            }
            else if (Laser.isThereError()) //*reading error, set value: 0.0 and send
            {
                payload_Data.distance = 0.0;
                payload_Data.signalQuality = 0;
                // SerialDebug.print("Slow_Msg Error : ");
                // SerialDebug.println(laserMsg.substring(4, 6));   //!new, fix this
                Laser.getError();

                errorTimerCounter = 0;
                if (errorStatus == 0)
                {
                    startErrorRepeatFlag = 1;
                    errorStatus = 1;
                }
                else
                    errorStatus = 2;
            }
        }
    }
}

ISR(TIMER1_OVF_vect) // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
    TCNT1 = 3036; // preload timer
    CentralTimer.mSecondCounter++;
    handleTimeoutCounter();
    if (CentralTimer.mSecondCounter % 1000 == 0)
        CentralTimer.secondCounter++;

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

    if (CentralTimer.mSecondCounter % dataFreq_mSec == 0)
        CentralTimer.timeSetFlag = 1;
    if (CentralTimer.mSecondCounter >= maxDuration_mSec)
        CentralTimer.mSecondCounter = 0;

    if (CentralTimer.secondCounter % dataFreq == 0)
        CentralTimer.timeSetFlag = 1;
    if (CentralTimer.secondCounter % dataFreq == 0) //data freq is a private member, chenge it to get function . or use enum
        dataFlag.Upd_Temperature = 1;
    if (CentralTimer.secondCounter % dataFreq == 0)
        dataFlag.Upd_Laser = 1;
    if (CentralTimer.secondCounter % dataFreq == 0)
        dataFlag.get_Console = 1;
    if (CentralTimer.secondCounter % dataFreq == 0)
        dataFlag.get_OpMode = 1;
    if (CentralTimer.secondCounter % dataFreq == 0)
        dataFlag.get_ReqTime = 1;
    if (CentralTimer.secondCounter >= maxDuration)
        CentralTimer.secondCounter = 0;
}
