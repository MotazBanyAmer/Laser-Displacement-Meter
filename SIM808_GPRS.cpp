#include "SIM808_GPRS.h"

//? should I create a class for wait funcitons!?
//* this may have to do with the timeout

String Message;
String stringValueExt;

void SIM808_GPRS::waitResp_sent()
{
    unsigned long respTime = 0;
    unsigned long currentTime = 0;
    currentTime = millis();
    status.done = 0;
    status.error = 0;

    while (!status.done)
    {
        if (SerialSIM.available())
        {
            String st = SerialSIM.readString(); //need to change becaose some responses have more than one
            if (st.indexOf("SEND OK") != -1)
            {
                Serial.println("SEND OK");
                Serial.println("value: " + stringValueExt);
                respTime = millis() - currentTime;
                Serial.println("Response Time: " + String(respTime));

                status.done = 1;
                status.fail = 0;
                status.error = 0;
            }
            if (st.indexOf("SEND status.fail") != -1)
            {
                Serial.println("SEND status.fail");
                Serial.println("value: " + stringValueExt);
                status.done = 1;
                status.fail = 1;
                status.error = 0;
            }
            if (st.indexOf("status.error") != -1)
            {
                Serial.println("SEND status.fail");
                Serial.println("value: " + stringValueExt);
                status.done = 1;
                status.fail = 0;
                status.error = 1;
            }
        }
    }
}

wiatResponse_t
waitResponse(uint8_t optionsNumber, option_t optionsData[], uint32_t timeoutTheshold)
{
    //continue here: this should be used as waiting function
    wiatResponse_t _Results;
    unsigned long _RespTime = 0;
    unsigned long _CurrentTime = 0;

    _Results.done = 0;
    _Results.error = 0;
    _Results.fail = 0;
    // Serial.println("TargetText: " + optionsData->text);

    _CurrentTime = millis();
    while (!_Results.done)
    {
        _RespTime = millis() - _CurrentTime;
        _Results.timeoutTime = _RespTime;
        if (_RespTime > timeoutTheshold)
        {
            _Results.done = 1;
            _Results.timeoutError = 1;
            return _Results;
        }
        else if (SerialSIM.available() > 0)
        {
            String incomingString = SerialSIM.readString();
            for (uint8_t _for_counter = 0; _for_counter < optionsNumber; _for_counter++)
            {
                if (incomingString.indexOf(optionsData[_for_counter].text) != -1)
                {
                    // _Results.response = optionsData[_for_counter].text;
                    _Results.response = incomingString;

                    _Results.error = optionsData[_for_counter].error;
                    _Results.fail = optionsData[_for_counter].fail;
                    //? when the fail and error is counted exactly???! in what case? review this
                    _Results.done = 1;
                    _Results.timeoutError = 0;
                    return _Results;
                }
            }
        }
    }
}
void SIM808_GPRS::waitResp_send()
{
    status.done = 0;
    status.error = 0;

    while (!status.done)
    {
        if (SerialSIM.available())
        {
            String st = SerialSIM.readString(); //need to change becaose some responses have more than one
            if (st.indexOf(">") != -1)
            {
                status.done = 1;
                status.error = 0;
            }
            if (st.indexOf("status.error") != -1)
            {
                status.done = 1;
                status.error = 1;
            }
        }
    }
}
void SIM808_GPRS::waitResp_start()
{
    status.done = 0;
    status.error = 0;
    while (!status.done)
    {
        while (SerialSIM.available())
        {
            String st = SerialSIM.readString();
            if (st.indexOf("CONNECT OK") != -1)
            {
                Serial.println("Start Good");
                status.error = 0;
                status.done = 1;
            }
            if (st.indexOf("ALREADY CONNECT") != -1)
            {
                Serial.println("Start Already");
                status.error = 0;
                status.done = 1;
            }
            if (st.indexOf("status.error") != -1)
            {
                Serial.println("Start Bad");
                status.done = 1;
                status.error = 0;
            }
        }
    }
}
void SIM808_GPRS::waitResp_OK()
{
    status.done = 0;
    status.error = 0;
    while (!status.done)
    {
        if (SerialSIM.available())
        {
            String st = SerialSIM.readString();
            //Serial.println("rcv" + st);
            if (st.indexOf("OK") != -1)
            {
                Serial.println("OK");
                status.error = 0;
                status.done = 1;
            }
            if (st.indexOf("status.error") != -1)
            {
                Serial.println("Start Bad");
                status.done = 1;
                status.error = 0;
            }
        }
    }
}
void SIM808_GPRS::waitResp_Shut()
{
    status.done = 0;
    status.error = 0;
    while (!status.done)
    {
        if (SerialSIM.available())
        {
            String st = SerialSIM.readString();
            //Serial.println("rcv" + st);
            if (st.indexOf("SHUT OK") != -1)
            {
                Serial.println("SHUT OK");
                status.error = 0;
                status.done = 1;
            }
            if (st.indexOf("status.error") != -1)
            {
                Serial.println("SHUT status.error");
                status.done = 1;
                status.error = 0;
            }
        }
    }
}

void resetDevice()
{
    pinMode(SIM_RST, OUTPUT);
    digitalWrite(SIM_RST, 0);
    delay(120);
    digitalWrite(SIM_RST, 1);
    delay(4000);
}
void SIM808_GPRS::setupBaseMessage()
{
    Message = "POST /api/v2/MotazBanyAmer/feeds/test/data HTTP/1.1\n";
    Message += "Host: io.adafruit.com\n";
    Message += "Content-Type: application/json\n";
    Message += "Content-Length: 18\n";
    Message += "X-AIO-Key: 4a2bddfff2b046caaa34a042ace1bba2\n\n";
    Message += "{\"value\":\"";
}
String SIM808_GPRS::setupPOSTMessage(String stringValue)
{
    stringValueExt = stringValue;
    return Message + stringValue + "\"}\n";
}
void SIM808_GPRS::updateProcedure(double updateValue) //send through GPRS port directly
{
    //  message
    SerialSIM.print(Start);
    waitResp_start();
    SerialSIM.print(Send);
    waitResp_send();
    SerialSIM.print(setupPOSTMessage(String(updateValue, 3)));
    //delay(100);
    SerialSIM.write(0x1A);
    Serial.println("Sending...");
    waitResp_sent();
}
void SIM808_GPRS::initConnection() //init GPRS direct connection, not HTTP
{
    Serial.println("Init Process");
    // Serial.print(Shut);
    SerialSIM.print(Shut);
    waitResp_Shut();
    //##add labels like (reseting connection) and (created a new connection) and other stuff here.
    //  delay(4000);
    // Serial.print(Mux0);
    SerialSIM.print(Mux0);
    waitResp_OK();
    //  delay(1000);
    // Serial.print(Cgatt);
    SerialSIM.print(Cgatt);
    waitResp_OK();
    //  delay(1000);
    // Serial.print(zain);
    SerialSIM.print(zain);
    waitResp_OK();
    //  delay(1000);
    // Serial.print(Cnct);
    SerialSIM.print(Cnct);
    waitResp_OK();
    //  delay(1000);
    //  Serial.print(IP);
    SerialSIM.print(IP);
    delay(350); //##create a funtion here instead of delay
    Serial.println("Init Done");
}