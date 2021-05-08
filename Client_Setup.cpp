#include "Client.h"

void adfruitio_Client::load_URL_POST(String feedKey)
{
    API_URL = buildAPI_URL(feedKey);
    load_HTTP_Parameter(__Para_URL, API_URL);
}
void adfruitio_Client::load_HTTP_Parameter(String para, String content)
{
    SerialSIM.println("AT+HTTPPARA=\"" + para + "\",\"" + content + '"');
    waitResp();
}
void adfruitio_Client::load_HTTP_Parameter(String para, String contentHeader, String headerValue)
{
    SerialSIM.println("AT+HTTPPARA=\"" + para + "\",\"" + contentHeader + ": " + headerValue + '"');
    waitResp();
}
void adfruitio_Client::load_HTTP_Data(String _value)
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
void adfruitio_Client::load_URL_GET(String feedKey, unsigned int limit)
{
    API_URL = buildAPI_URL(feedKey, limit);
    load_HTTP_Parameter(__Para_URL, API_URL);
}
void adfruitio_Client::load_HTTP_Headers()
{
    load_HTTP_Parameter(__Para_Userdata, __hdr_x_aio_key, x_aio_key);
    //debugResp(__resp);
    load_HTTP_Parameter(__Para_content, content_value);
    //debugResp(__resp);
}

String adfruitio_Client::buildAPI_URL(String _feedKey)
{
    String result = "https://io.adafruit.com/api/v2/" + String(adafruit_userName) + "/feeds/" + String(_feedKey) + "/data";
    return result;
}
String adfruitio_Client::buildAPI_URL(String _feedKey, int _limit)
{
    String result = "https://io.adafruit.com/api/v2/" + String(adafruit_userName) + "/feeds/" + String(_feedKey) + "/data?limit=" + String(_limit);
    return result;
}
String adfruitio_Client::buildJSON_snglObj(String JSON_name, String JSON_value)
{
    //todo: thim may be moved to JSON
    return "{\"" + JSON_name + "\":\"" + JSON_value + "\"}";
}


void adfruitio_Client::httpsInit()
{
    SerialSIM.println(HTTPInit);
    waitResp();
    SerialSIM.println(HTTPSSL);
    waitResp();
}

void adfruitio_Client::initlize_HTTPs()
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

void adfruitio_Client::parseHTTP_read(String readResp)
{ //((5)) this get one object not an array, need to be updated for array.
    int temp1;
    int temp2;
    temp1 = readResp.indexOf("{");
    temp2 = readResp.indexOf("}", temp1);
    HTTPread_dataContent = readResp.substring(temp1, temp2 + 1);
    //SerialDebug.println("HTTPread_dataContent: " + HTTPread_dataContent);
}

int adfruitio_Client::getRespMeta(String respMeta)
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

void adfruitio_Client::debugResp(byte debugPayload = 0x00, String _text = " ")
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