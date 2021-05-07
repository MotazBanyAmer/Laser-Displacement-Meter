
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
void debugResp(byte debugPayload = 0x00, String _text = " ")

//wait resp Types: null :OK || 1, check and Get Payload || 2: check content
void waitResp(String textOK = respOk, String textError = respError)

void checkSimDevice();
void httpsInit();

String buildAPI_URL(String _feedKey);
String buildAPI_URL(String _feedKey, int _limit);

void load_HTTP_Parameter(String para, String content);
void load_HTTP_Parameter(String para, String contentHeader, String headerValue);
int getRespMeta(String respMeta);

void action_POST();
void action_GET();
String buildJSON_snglObj(String JSON_name, String JSON_value);
void load_HTTP_Data(String _value);
void parseHTTP_read(String readResp);
void readHTTP_resp();

void initlize_HTTPs();
void load_URL_POST(String feedKey);
void load_URL_GET(String feedKey, unsigned int limit);
void load_HTTP_Headers();
void send_POST(String feed, String _value);
void send_GET(String feed, int dataLimit = 1);

    

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