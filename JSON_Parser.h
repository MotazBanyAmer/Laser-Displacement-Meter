
#ifndef __JSON_PARSER_H
#define __JSON_PARSER_H
//String msg = "{\"id\":\"0EBPS3V80VH8EFWPGY4VYWS1FN\",\"value\":\"FAST\",\"feed_id\":1271480,\"feed_key\":\"laser-feeds.operation-mode\",\"created_at\":\"2020-01-20T22:15:13Z\",\"created_epoch\":1579558513,\"expiration\":\"2020-02-19T22:15:13Z\"}";
#include "Arduino.h"
#include "appCommon.h"
#include "appConfig.h"

#define dqString "\""
#define comma ","
#define colon ":"

class JSON_Parser
{
public:
    String getNames();
    String getValues(String context1, String context2);
    byte getPairsCount();
    void getAllJSON(String JSONobj);
    String getCertainString(String JSONobj, String searchName);
    long getCertainNumber(String JSONobj, String searchName);

private:
    String names[7];
    String values[7];
    String tempMsg;
};
/*
  #define __number        0   //Int type
  #define __largeNumber   1   //Long type
  #define __String        2   //String Type
  #define __JSON_obj      3   //not implemented yet
  #define __JSON_arr      4   //not implemented yet
*/

#endif