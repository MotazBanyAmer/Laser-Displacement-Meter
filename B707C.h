#ifndef __B707C_H__
#define __B707C_H__

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
    //Print
    void printSQ();
    void printError();
    //Wait
    void waitResp_Dist();
    void waitResp_Temp();

    //Setters


    //Getters
    double getDistance();
    double getTemp();
    double getVlt();
    int getSignalQuality();

    //Status
    void getError();
    bool isDone() { return doneLaser; }
    bool isThereError() { return errorLaser; }

    //Funciton Commands
    void laserOn();
    void laserOff();

    //Data Commands
    void demandStatus();
    void demandData(char msgID);

private:
    // boolean timeoutErrorFlag; //!new: used in "Code_def" but commented out

    //unsigned long timeoutCounter;//!new: used in alot of places but commented out
    //unsigned long currentTime; //!new: used in alot of places but commented out, also have a lot of instances as local variable of hte same name

    // boolean startTimeoutFlag = 0; //!new: used in "Code_def" but commented out

    boolean doneLaser = 0;
    boolean errorLaser = 0;

    boolean msgEnd; //!this is used bu I belive it need review
    String LaserRcv = " ";
    char rcvChar = ' ';

    int errorID;       //! I believe this was built in stupid quick way, need to be reviewd
    boolean errorFlag; //! mostly, need to be moved

    String laserMsg; //* used in main code!

    char laserRcv[14];

    double distance = 0;   //* used in the main code
    int signalQuality = 0; //* used in the main code

    double temperature; //* used in the main code,+other places
    // double voltage; //* not used yet, shall be used in the main code + this may be moved to other place!
};
#endif