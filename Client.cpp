#include "Client.h"

adfruitio_Client::adfruitio_Client(/* args */)
{
}

adfruitio_Client::~adfruitio_Client()
{
}

String adfruitio_Client::get_Resp_value()
{
    return JSONResp_value;
}
String adfruitio_Client::get_Resp_id()
{
    return JSONResp_id;
}

void adfruitio_Client::send_POST(String feed, String _value)
{
    SystemLogger logger_sendPOST("Sending Post");

    //load_HTTP_Parameter(__Para_CID, CID_value); // need to review the message to send
    //debugResp(__resp);
    load_URL_POST(feed);
    logger_sendPOST.add_microLog_plain("feed loaded");
    logger_sendPOST.push_log();

    //debugResp(__resp);
    //load_HTTP_Headers();
    load_HTTP_Parameter(__Para_Userdata, __hdr_x_aio_key, x_aio_key);
    logger_sendPOST.add_microLog_plain("key loaded");
    logger_sendPOST.push_log();
    //debugResp(__resp);
    load_HTTP_Parameter(__Para_content, content_value);
    logger_sendPOST.add_microLog_plain("content_value loaded");
    logger_sendPOST.push_log();
    //debugResp(__resp);
    load_HTTP_Data(_value);
    logger_sendPOST.add_microLog_plain("data loaded");
    logger_sendPOST.push_log();
    //debugResp(__resp);
    //done or error .. read response code, then read data if needed
    //later parse data if needed
    logger_sendPOST.add_microLog_plain("Updating...");
    logger_sendPOST.push_log();
    action_POST();
    logger_sendPOST.add_log_plain("action_POST");
    logger_sendPOST.push_log();

    //debugResp(__resp);
    getRespMeta(results.response); //todo: this to be got from action post, not as global

    logger_sendPOST.add_log_plain("getRespMeta");
    //SerialDebug.println(respCode);
    //SerialDebug.println(respMethod);
    //SerialDebug.println(dataLength);

    logger_sendPOST.add_log_parameter("respCode", respCode);
    if (respCode == "200")
    {
        readHTTP_resp(); //? should I change name!
        logger_sendPOST.add_microLog_plain("Updating Successfull!");
    }

    JSONResp_value = getCertainString(HTTPread_dataContent, "value");
    JSONResp_id = getCertainString(HTTPread_dataContent, "id");
    String tempLogMsg = "Sent: \"" + JSONResp_value + "\", to: \"" + feed + "\"";
    logger_sendPOST.add_log_plain(tempLogMsg);
    logger_sendPOST.push_log();
    //SerialDebug.println("POST - JSON value: " + JSONResp_value); // this most likly to not be used here, this should be in get only, ((4))
    //SerialDebug.println("POST - JSON id: " + JSONResp_id); // this most likly to not be used here, this should be in get only, ((4))
}
void adfruitio_Client::send_GET(String feed, int dataLimit = 1)
{
    //load_HTTP_Parameter(__Para_CID, CID_value); // need to review the message to send
    //debugResp(__resp);
    load_URL_GET(feed, dataLimit);
    //debugResp(__resp);
    load_HTTP_Parameter(__Para_Userdata, __hdr_x_aio_key, x_aio_key);
    //debugResp(__resp);
    action_GET();
    getRespMeta(results.response);
    //debugResp(__resp);
    //SerialDebug.println("((5))" + results.response);
    getRespMeta(results.response);
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
