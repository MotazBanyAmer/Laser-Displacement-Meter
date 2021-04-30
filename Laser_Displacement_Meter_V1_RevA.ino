#include "Common.h"
#include "ErrorHandler.h"
#include "GPRS_Fun.h"
#include "Laser_Fun.h"
#include "HTTP_msgs.h"
#include "Code_def.h"
//test
void initProject();
void startup_actions();
void startup_actions()
{
  //startup_melody(); //TODO enable this at the end!
  //startMelody();    //!One of these shall be deleted

  SerialDebug.println("Start");
}
void startup_melody();

void setup()
{
  initProject(); //Initialize project
  startup_actions();

  //reset SIM when program start after deloying the final application

  //setting up
  //GPRS
  //setupBaseMessage();
  /*
    pinMode(SIM_RST, OUTPUT);
    digitalWrite(SIM_RST, 0);
    delay(120);
    digitalWrite(SIM_RST, 1);
    delay(4000);
  */
  //waitResp("+CFUN");
  checkSimDevice();
  //HTTPInitSucsMelody();
  //delay(500);
  SerialDebug.println("Configure HTTP");
  initlize_HTTPs();
  //HTTPInitSucsMelody();
  if (globalDone)
  SerialDebug.println("HTTP Configured");

  SerialDebug.println("Init HTTP!");
  httpsInit();
  //waitResp();
  //debugResp(__resp);
  if (globalDone)
    SerialDebug.println("HTTP Ready");

  //initConnection();
}

byte Upd_Laser2 = 1; // for testing
void loop()
{
  if (Upd_Laser)
  //  if (0)
  {
    SerialDebug.println();
    SerialDebug.println("*************Update Laser*************");
    SerialDebug.println();
    SerialDebug.println("Request Dist");
    demandData(SlowMode_Byte);
    //SerialDebug.println("Waiting");
    waitResp_Dist();
    //SerialDebug.println("Response Receive");
    if (doneLaser)
    {
      //SerialDebug.print("(3)"); SerialDebug.println(LaserRcv);
      if (errorLaser == 0) //*reading success, send the reading
      {
        //SerialDebug.println("Reading Laser -- Slow");
        distance = getDistance();
        signalQuality = getSQ();

        SerialDebug.print("Distance : ");
        SerialDebug.println(distance, 3);
        SerialDebug.print("signal Quality : ");
        SerialDebug.println(signalQuality);
      }
      else if (errorLaser == 1) //*reading error, set value: 0.0 and send
      {
        distance = 0.0;
        signalQuality = 0;
        SerialDebug.print("Slow_Msg Error : ");
        SerialDebug.println(laserMsg.substring(4, 6));
        getError();
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
    //    lastCommand = SlowMode_Byte;

    //updateProcedure(distance);
    send_POST(__feeds_lsrDist, String(distance, 3));
    SerialDebug.println("Sent: \"" + JSONResp_value + "\", to: \"" + __feeds_lsrDist + "\"");
    send_POST(__feeds_lsrSigQ, String(signalQuality));
    SerialDebug.println("Sent: \"" + JSONResp_value + "\", to: \"" + __feeds_lsrSigQ + "\"");
    Upd_Laser = 0;
    SerialDebug.println("-----------------------------------------");
    //updateIO = 0;
  }
  //check the rest of the code, and see if the laser message works at its simplist form
  //later on add the rest of the messages of hte laser
  //also, add the rest of GPRS messages
  if (get_Console)
  //  if (0)
  {
    SerialDebug.println();
    SerialDebug.println("*************get_Console*************");
    SerialDebug.println();
    send_GET(__feeds_console);
    SerialDebug.println("Got: \"" + JSONResp_value + "\", from: \"" + __feeds_console + "\"");

    get_Console = 0;
    SerialDebug.println("-----------------------------------------");
  }
  if (get_OpMode)
  //  if (0)
  {
    SerialDebug.println();
    SerialDebug.println("*************get_OpMode*************");
    SerialDebug.println();
    send_GET(__feeds_OPModes);
    SerialDebug.println("Got: \"" + JSONResp_value + "\", from: \"" + __feeds_OPModes + "\"");

    get_OpMode = 0;
    SerialDebug.println("-----------------------------------------");
  }
  if (get_ReqTime)
  //  if (0)
  {
    SerialDebug.println();
    SerialDebug.println("*************get_ReqTime*************");
    SerialDebug.println();
    send_GET(__feeds_reqTime);
    SerialDebug.println("Got: \"" + JSONResp_value + "\", from: \"" + __feeds_reqTime + "\"");
    /* pasre JSON and get:
        id: to check if the value updated or not
        if actully updated -> do with the value
        get value :: which is req time,
        change the update time according to it.
    */
    get_ReqTime = 0;
    SerialDebug.println("-----------------------------------------");
  }
  if (Upd_Temperature)
  {
    SerialDebug.println();
    SerialDebug.println("*************Upd_Temperature*************"); //
    SerialDebug.println();
    SerialDebug.println("Request Temp");
    demandStatus();
    waitResp_Temp();
    temperature = getTemp();
    SerialDebug.println(temperature);
    send_POST(__feeds_temprtr, String(temperature, 2));
    SerialDebug.println("Sent: \"" + JSONResp_value + "\", to: \"" + __feeds_temprtr + "\"");
    //read temperature from laser
    //update laser
    //send_POST("laser-feeds.temperature", );
    Upd_Temperature = 0;
    SerialDebug.println("-----------------------------------------");
  }
}
void initProject()
{
  SerialDebug.begin(115200);
  SerialSIM.begin(115200);
  SerialBT.begin(115200);
  SerialLaser.begin(19200);

  SerialSIM.setTimeout(5);
  SerialLaser.setTimeout(5);

  pinMode(buzzerPin, OUTPUT);

  setupTimer();
}
void startup_melody()
{
  tone(buzzerPin, NOTE_C6, shortTone3);
  delay(shortTone3 * mult1);
  tone(buzzerPin, NOTE_C6, shortTone3);
  delay(shortTone3 * mult1);
}