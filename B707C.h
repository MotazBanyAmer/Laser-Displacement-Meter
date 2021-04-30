#ifndef __B707C_H__
#define __B707C_H__

#include "Arduino.h"
#include "appConfig.h"
#include "B707C_Constants.h"

// #define timeoutDuration 1 //in seconds
#define maxDuration 200 //in seconds
#define timeoutDuration 4
#define errorDuration 4

byte errorTrialsCounter;

// #define dataFreq 15 //in seconds
byte dataFreq = 15;

class B707C
{
public:
    double getDistance();
    void waitResp_Temp();
    double getSQ();
    void printSQ();
    double getTemp();
    double getVlt();
    void getError();

    void printError();
    void laserOn();
    void laserOff();
    void demandStatus();
    void demandData(char msgID);

private:
    boolean checkTimeout;
    boolean timeoutSpecial;
    boolean timeoutErrorFlag;
    boolean errorReading;

    //unsigned long timeoutCounter;
    //unsigned long currentTime;
    //boolean timeoutTrialFlag;
    //boolean timeSetFlag = 0;

    boolean startErrorRepeatFlag = 0;
    boolean errorTimerCounter = 0;
    boolean errorDemand = 0;
    byte errorStatus = 0; //0: no error, 1: new error, 2: error continoues

    char lastCommand;
    boolean startTimeoutFlag = 0;

    byte timeoutTrialsCounter;
    enum lsrMsgs
    {
        On_Msg,
        Off_Msg,
        Stat_Msg,
        Auto_Msg,
        Slow_Msg,
        Fast_Msg
    };

    boolean parseData = 0;

    boolean msgEnd;
    String LaserRcv = " ";
    char rcvChar = ' ';
    int dataLocation;

    int errorID;
    boolean errorFlag;

    int expLsrMsg;
    int msgCounter;
    String laserMsg;

    char laserRcv[14];
    boolean laserFlag = 0;
    double distance = 0;
    int signalQuality = 0;

    double temperature;
    double voltage;
}

#endif