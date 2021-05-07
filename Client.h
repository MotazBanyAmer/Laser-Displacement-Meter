
#ifndef __CLIENT_H
#define __CLIENT_H

#include "Connection_meta.h"
#include "JSON_Parser.h"

//@URL
#define __Para_URL "URL"
#define adafruit_userName "MotazBanyAmer"
#define HTTP_Data_Timeout 2000

#define __done 0b00000001
#define __error 0b00000010
#define __text 0b00000100
#define __resp 0b00001000
#define __respTime 0b00010000

class adfruitio_Client
{
public:
    adfruitio_Client(/* args */);
    ~adfruitio_Client();
    String API_URL;

private:
    /* data */
    boolean globalDone = 0;
    boolean globalError = 0;
    String globalResp = " ";
    unsigned long globalRespTime = 0;
    unsigned long globalCurrentTime = 0;

    String respMethod;
    String respCode;
    int dataLength;

    String value;
    int HTTPread_datalength; // maybe used for confirming the message is right
    String HTTPread_dataContent;
};

#endif