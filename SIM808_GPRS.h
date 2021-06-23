#ifndef __SIM808_GPRS_H__
#define __SIM808_GPRS_H__

#include "Arduino.h"
#include "appCommon.h"
#include "appConfig.h"

#define AT "AT\n"
#define Shut "AT+CIPSHUT\n"
#define Mux0 "AT+CIPMUX=0\n"
#define Cgatt "AT+CGATT=1\n"
#define zain "AT+CSTT=\"zain\",\"zain\",\"zain\"\n"
#define Cnct "AT+CIICR\n"
#define IP "AT+CIFSR\n"
#define Start "AT+CIPSTART=\"TCP\",\"io.adafruit.com\",\"80\"\n"
#define Send "AT+CIPSEND\n"
#define Cnct "AT+CIICR\n"
#define SUB 0x1A

#define deactivated "+PDP: DEACT"


//todo: convert this to struct or somthing

#define SIM_RST 53

class SIM808_GPRS
{
public:
    void initConnection();
    void setupBaseMessage(); //not used (commented out)
    String setupPOSTMessage(String stringValue);
    void updateProcedure(double updateValue);
    void resetDevice();
    void waitResp_sent();
    void waitResp_send();
    void waitResp_start();
    void waitResp_OK();
    void waitResp_Shut();

private:
    struct Status
    {
        bool done;
        bool error;
        bool fail;
    } status;
};

typedef struct result
{
    uint8_t progress;
    bool error;
    bool done;
    bool fail;
    bool timeoutError;
    uint32_t timeoutTime;
    String response;
} wiatResponse_t;

typedef struct Options
{
    String text;
    bool error;
    bool fail;
} option_t;

wiatResponse_t waitResponse(uint8_t optionsNumber, option_t optionsData[], uint32_t timeoutTheshold);
//& where to continue: I have stopped here after the code verified
//look into line 24 in Client HTTP actions.cpp. I'm tested this in Post and Get
//to replace old wiatResp method, and to test time issues
//I have stopped due to not being able to use my sim card due to low balance
#endif