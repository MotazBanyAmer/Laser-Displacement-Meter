#include "Client.h"

void adfruitio_Client::action_POST()
{
    SerialSIM.println("AT+HTTPACTION=1");
    waitResp("+HTTPACTION");
    //debugResp(__resp);
    waitResp("+HTTPACTION:");
    //debugResp(__resp);
    //wait OK
    //wait HTTPACTION... with timeout
    //raise a flag for error or done...
    //mey need to return response code and some other meta data.
}
void adfruitio_Client::action_GET()
{
    SerialSIM.println("AT+HTTPACTION=0");
    waitResp("+HTTPACTION");
    //debugResp(__resp);
    waitResp("+HTTPACTION:");
    //debugResp(__resp);
    //wait OK
    //wait HTTPACTION... with timeout
    //raise a flag for error or done...
}
void adfruitio_Client::readHTTP_resp()
{
    SerialSIM.println("AT+HTTPREAD");
    waitResp("+HTTPREAD:");
    //debugResp(__resp);
    waitResp();
    //debugResp(__resp);
    parseHTTP_read(globalResp);
}

void adfruitio_Client::checkSimDevice()
{
    Serial.println("System Start");
    Serial.println("Checking SIM");
    SerialSIM.println("AT");
    waitResp();
    if (globalDone) //todo, what is this!
    {
        globalDone = 0;
        Serial.println("SIM Device Found");
    }
}

//wait resp Types: null :OK || 1, check and Get Payload || 2: check content
void adfruitio_Client::waitResp(String textOK = respOk, String textError = respError)
{
    //unsigned long tempRespTime = 0;
    //unsigned long tempCurrentTime = 0;
    //tempCurrentTime = micros();
    boolean tempDone = 0;
    boolean tempError = 0;
    String tempResp = " ";
    //SerialDebug.println(textOK);
    //SerialDebug.println(textError);

    while (!tempDone)
    {
        //SerialDebug.println("(3)");
        if (SerialSIM.available())
        {
            //SerialDebug.println("(4)");
            tempResp = SerialSIM.readString(); //need to change becaose some responses have more than one
            //SerialDebug.println(tempResp);
            //tempRespTime = micros() - tempCurrentTime;
            if (tempResp.indexOf(textOK) != -1) //this should work unless the message content contains the message, like recieving OK in a HTTPREAD message.
            {
                //SerialDebug.println("(1)");
                tempDone = 1;
                tempError = 0;
            }

            if (tempResp.indexOf(textError) != -1)
            {
                //SerialDebug.println("(2)");
                tempDone = 1;
                tempError = 1;
            }
        }
    }

    globalDone = tempDone;
    globalError = tempError;
    globalResp = tempResp;
    //globalRespTime = tempRespTime;
    //globalCurrentTime = tempCurrentTime;

}
