#include "B707C.h"
#include "TimerConfig.h"
#include "Timeout.h"
#include "Central.h"
#include "Errors_handler.h""
#include "Logger.h"

B707C Laser;

// ISR(TIMER1_OVF_vect);

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
        SystemLogger logger_Upd_Laser("Aquiring laser");

        Laser.demandData(static_cast<char>(B707C_dModes::SlowMode));
        Laser.waitResp_Dist();

        if (Laser.isDone())
        {
            if (!Laser.isThereError()) //*reading success, send the reading
            {
                payload_Data.distance = Laser.getDistance();
                payload_Data.signalQuality = Laser.getSignalQuality();

                logger_Upd_Laser.add_log_plain("Laser OK");
                logger_Upd_Laser.add_log_parameter("Distance", payload_Data.distance, 3);
                logger_Upd_Laser.add_log_parameter("signalQuality", payload_Data.signalQuality, 2);
                logger_Upd_Laser.push_log();
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

        //todo: post online

        dataFlag.Upd_Laser = 0;
    }
    if (dataFlag.get_Console)
    {
        SystemLogger logger_getConsole("Getting Console");
        //todo: GET command

        dataFlag.get_Console = 0;
    }
    if (dataFlag.get_OpMode)
    {
        SystemLogger logger_getOpMode("Getting Op Mode");
        //todo: GET command

        dataFlag.get_OpMode = 0;
    }
    if (dataFlag.get_ReqTime)
    {
        SystemLogger logger_getReqTime("Getting Request Time");
        //todo: GET command

        dataFlag.get_ReqTime = 0;
    }
    if (dataFlag.Upd_Temperature)
    {
        SystemLogger logger_Upd_Temperature("Aquiring laser");

        Laser.demandStatus();
        Laser.waitResp_Temp();
        payload_Data.temperature = Laser.getTemp();

        //todo: send post
        logger_Upd_Temperature.add_log_parameter("Temperature", payload_Data.temperature, 2);
        logger_Upd_Temperature.push_log();
        dataFlag.Upd_Temperature = 0;
    }
}
int tempx1 = 0;
ISR(TIMER1_OVF_vect) // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
    TCNT1 = timerFq_1000Hz; // preload timer

    CentralTimer.mSecondCounter++;
    handleTimeoutCounter();
    // Serial.println("mSecondCounter: " + String((uint32_t)CentralTimer.mSecondCounter));
    if (CentralTimer.mSecondCounter % 1000 == 0)
    {
        CentralTimer.secondCounter++;
        // Serial.println("CentralTimer1: " + String(CentralTimer.secondCounter));
    }

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
    {
        CentralTimer.timeSetFlag = 1;
    }

    if (CentralTimer.mSecondCounter >= maxDuration_mSec)
    {
        CentralTimer.mSecondCounter = 0;
    }

    if (CentralTimer.secondCounter > 0)
    {
        if (CentralTimer.secondCounter % dataFreq == 0)
        {
            CentralTimer.timeSetFlag = 1;
        }
        if (CentralTimer.secondCounter % dataFreq == 0) //data freq is a private member, chenge it to get function . or use enum
        {
            dataFlag.Upd_Temperature = 1;

            // Serial.println("dataFreq mod: " + String(CentralTimer.secondCounter % dataFreq));
            // Serial.println("CentralTimer: " + String(CentralTimer.secondCounter));
            // Serial.println("dataFreq: " + String(dataFreq));
            // Serial.println("tempx1: " + String(tempx1++));
        }
        if (CentralTimer.secondCounter % dataFreq == 0)
        {
            dataFlag.Upd_Laser = 1;
        }
        if (CentralTimer.secondCounter % dataFreq == 0)
        {
            dataFlag.get_Console = 1;
        }
        if (CentralTimer.secondCounter % dataFreq == 0)
        {
            dataFlag.get_OpMode = 1;
        }
        if (CentralTimer.secondCounter % dataFreq == 0)
        {
            dataFlag.get_ReqTime = 1;
        }
    }
    if (CentralTimer.secondCounter >= maxDuration)
    {
        CentralTimer.secondCounter = 0;
    }
}
