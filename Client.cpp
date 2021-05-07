#include "Client.h"

adfruitio_Client::adfruitio_Client(/* args */)
{
}

adfruitio_Client::~adfruitio_Client()
{
}

void debugResp(byte debugPayload = 0x00, String _text = " ")
{
    if (debugPayload & __done)
        Serial.println("Done: " + String(globalDone));
    if (debugPayload & __error)
        Serial.println("Error: " + String(globalError)); //##check here
    if (_text != " ")
        Serial.println("Text: " + String(_text));
    if (debugPayload & __resp)
        Serial.println("Response: " + globalResp);
    if (debugPayload & __respTime)
        Serial.println("Response Time: " + String(globalRespTime));
}

//wait resp Types: null :OK || 1, check and Get Payload || 2: check content
void waitResp(String textOK = respOk, String textError = respError)
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

    //SerialDebug.println("globalDone : " + String(globalDone));
    //SerialDebug.println("globalError : " + String(globalError));
    //SerialDebug.println("globalResp : " + String(globalResp));
}

void checkSimDevice()
{
    Serial.println("System Start");
    Serial.println("Checking SIM");
    SerialSIM.println("AT");
    waitResp();
    if (globalDone)
    {
        globalDone = 0;
        Serial.println("SIM Device Found");
    }
}
void httpsInit()
{
    SerialSIM.println(HTTPInit);
    waitResp();
    SerialSIM.println(HTTPSSL);
    waitResp();
}

String buildAPI_URL(String _feedKey)
{
    String result = "https://io.adafruit.com/api/v2/" + String(adafruit_userName) + "/feeds/" + String(_feedKey) + "/data";
    return result;
}
String buildAPI_URL(String _feedKey, int _limit)
{
    String result = "https://io.adafruit.com/api/v2/" + String(adafruit_userName) + "/feeds/" + String(_feedKey) + "/data?limit=" + String(_limit);
    return result;
}

void load_HTTP_Parameter(String para, String content)
{
    SerialSIM.println("AT+HTTPPARA=\"" + para + "\",\"" + content + '"');
    waitResp();
}
void load_HTTP_Parameter(String para, String contentHeader, String headerValue)
{
    SerialSIM.println("AT+HTTPPARA=\"" + para + "\",\"" + contentHeader + ": " + headerValue + '"');
    waitResp();
}
int getRespMeta(String respMeta)
{ //check that ((3))
    byte temp1 = respMeta.indexOf("+HTTPACTION");
    if (temp1 != -1) // may need to use indexof(":") or somthing to detect the begining of the meta, in case of multi Resp.
    {
        respMethod = respMeta.substring(temp1 + 13, temp1 + 14); //location of (x) in x,###,###
        //SerialDebug.println("respMethod:: " + respMethod);
        respCode = respMeta.substring(temp1 + 15, temp1 + 18); //location of first (x) and last (x) in #,xxx,###
        //SerialDebug.println("respCode:: " + respCode);
        respMeta.remove(0, temp1 + 19); //location of last ',' in #,###,xxx
        dataLength = respMeta.toInt();  //may need change numbers to get :
                                        //SerialDebug.println("dataLength:: " + String(dataLength));
    }
}

void action_POST()
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
void action_GET()
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
String buildJSON_snglObj(String JSON_name, String JSON_value)
{
    return "{\"" + JSON_name + "\":\"" + JSON_value + "\"}";
}
void load_HTTP_Data(String _value)
{
    String JSONObjMsg = buildJSON_snglObj("value", _value);
    //String JSONObjMsg = buildJSON_snglObj("value", "20.336");
    SerialSIM.println("AT+HTTPDATA=" + String(JSONObjMsg.length()) + ',' + String(HTTP_Data_Timeout));
    waitResp(respDownload);
    //SerialDebug.Println("Downloading Data");
    //debugResp(__resp);
    SerialSIM.println(JSONObjMsg);
    waitResp();
    //SerialDebug.Println("Downloading satatus:");
    //debugResp(__resp);
}
void parseHTTP_read(String readResp)
{ //((5)) this get one object not an array, need to be updated for array.
    int temp1;
    int temp2;
    temp1 = readResp.indexOf("{");
    temp2 = readResp.indexOf("}", temp1);
    HTTPread_dataContent = readResp.substring(temp1, temp2 + 1);
    //SerialDebug.println("HTTPread_dataContent: " + HTTPread_dataContent);
}
void readHTTP_resp()
{
    SerialSIM.println("AT+HTTPREAD");
    waitResp("+HTTPREAD:");
    //debugResp(__resp);
    waitResp();
    //debugResp(__resp);
    parseHTTP_read(globalResp);
}

void initlize_HTTPs()
{
    SerialSIM.print(SgnlStr);
    waitResp();
    debugResp(__resp);
    SerialSIM.print(Provider);
    waitResp();
    debugResp(__resp);
    SerialSIM.print(APN);
    waitResp();
    debugResp(__resp);
    SerialSIM.print(GPRSType);
    waitResp();
    debugResp(__resp);
    SerialSIM.print(query1);
    waitResp();
    debugResp(__resp);
    SerialSIM.print(checkIP);
    waitResp();
    debugResp(__resp);
    load_HTTP_Parameter(__Para_CID, CID_value); // need to review the message to send
    debugResp(__resp);
}
void load_URL_POST(String feedKey)
{
    API_URL = buildAPI_URL(feedKey);
    load_HTTP_Parameter(__Para_URL, API_URL);
}
void load_URL_GET(String feedKey, unsigned int limit)
{
    API_URL = buildAPI_URL(feedKey, limit);
    load_HTTP_Parameter(__Para_URL, API_URL);
}
void load_HTTP_Headers()
{
    load_HTTP_Parameter(__Para_Userdata, __hdr_x_aio_key, x_aio_key);
    //debugResp(__resp);
    load_HTTP_Parameter(__Para_content, content_value);
    //debugResp(__resp);
}
void send_POST(String feed, String _value)
{
    //load_HTTP_Parameter(__Para_CID, CID_value); // need to review the message to send
    //debugResp(__resp);
    load_URL_POST(feed);
    //debugResp(__resp);
    //load_HTTP_Headers();
    load_HTTP_Parameter(__Para_Userdata, __hdr_x_aio_key, x_aio_key);
    //debugResp(__resp);
    load_HTTP_Parameter(__Para_content, content_value);
    //debugResp(__resp);
    load_HTTP_Data(_value);
    //debugResp(__resp);
    //done or error .. read response code, then read data if needed
    //later parse data if needed
    SerialDebug.println("Updating...");
    action_POST();
    //debugResp(__resp);
    getRespMeta(globalResp);
    //SerialDebug.println(respCode);
    //SerialDebug.println(respMethod);
    //SerialDebug.println(dataLength);

    if (respCode == "200")
    {
        readHTTP_resp();
        SerialDebug.println("Updating Success Successfully!");
    }
    JSONResp_value = getCertainString(HTTPread_dataContent, "value");
    JSONResp_id = getCertainString(HTTPread_dataContent, "id");
    //SerialDebug.println("POST - JSON value: " + JSONResp_value); // this most likly to not be used here, this should be in get only, ((4))
    //SerialDebug.println("POST - JSON id: " + JSONResp_id); // this most likly to not be used here, this should be in get only, ((4))
}
void send_GET(String feed, int dataLimit = 1)
{
    //load_HTTP_Parameter(__Para_CID, CID_value); // need to review the message to send
    //debugResp(__resp);
    load_URL_GET(feed, dataLimit);
    //debugResp(__resp);
    load_HTTP_Parameter(__Para_Userdata, __hdr_x_aio_key, x_aio_key);
    //debugResp(__resp);
    action_GET();
    getRespMeta(globalResp);
    //debugResp(__resp);
    //SerialDebug.println("((5))" + globalResp);
    getRespMeta(globalResp);
    //SerialDebug.println(respCode);
    //SerialDebug.println(respMethod);
    //SerialDebug.println(dataLength);

    if (respCode == "200")
    {
        readHTTP_resp();
        SerialDebug.println("Getting Data Successfully!");
    }

    JSONResp_value = getCertainString(HTTPread_dataContent, "value");
    JSONResp_id = getCertainString(HTTPread_dataContent, "id");
    //SerialDebug.println("GET- JSON value: " + JSONResp_value); // this most likly to not be used here, this should be in get only, ((4))
    //SerialDebug.println("GET- JSON id: " + JSONResp_id); // this most likly to not be used here, this should be in get only, ((4))
    //done or error .. read data
    //later parse data
}
