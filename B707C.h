#ifndef __B707C_H__
#define __B707C_H__

#include "Arduino.h"
#include "B707C_Constants.h"

#include "appConfig.h"
#include "appCommon.h"

// #define timeoutDuration 1 //in seconds
#define maxDuration 200 //in seconds
#define timeoutDuration 4
#define errorDuration 4

// #define dataFreq 15 //in seconds

class B707C
{
public:
    double getDistance();
   void waitResp_Dist();
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
    // boolean timeoutErrorFlag; //!new: used in "Code_def" but commented out

    //unsigned long timeoutCounter;//!new: used in alot of places but commented out
    //unsigned long currentTime; //!new: used in alot of places but commented out, also have a lot of instances as local variable of hte same name

    boolean startErrorRepeatFlag = 0; //!new, I think this should noe be here
    boolean errorTimerCounter = 0;    //!new, I think this should noe be here
    byte errorStatus = 0;             //0: no error, 1: new error, 2: error continoues //TODO:review this, this should be as modern enum or namespace or defines!

    // boolean startTimeoutFlag = 0; //!new: used in "Code_def" but commented out

    boolean doneLaser = 0;
    boolean errorLaser = 0;

    byte dataFreq = 15; //TODO: I believe this should be moved
                        /*
    !mostly, this was replaced with defines in constants,
    * //TODO, this this 
    enum lsrMsgs
    {
        On_Msg,
        Off_Msg,
        Stat_Msg,
        Auto_Msg,
        Slow_Msg,
        Fast_Msg
    };
    */

    boolean msgEnd; //!this is used bu I belive it need review
    String LaserRcv = " ";
    char rcvChar = ' ';

    int errorID;    //! I believe this was built in stupid quick way, need to be reviewd
    boolean errorFlag;  //! mostly, need to be moved

    String laserMsg;    //* used in main code! 

    char laserRcv[14];

    double distance = 0;    //* used in the main code
    int signalQuality = 0;  //* used in the main code

    double temperature;     //* used in the main code,+other places
    // double voltage; //* not used yet, shall be used in the main code + this may be moved to other place!
};
#endif