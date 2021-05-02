#include "Logger.h"
#include "appConfig.h"
#define SerialLogger SerialDebug

SystemLogger::SystemLogger(String Context) //:tempContext(Context), templogRefNum(logRefNum)
{
    // Serial.println("~Constructing");
    logMessage_push = "";
    templogStack = ++logStack;
    for (int i = 1; i < templogStack; i++)
    {
        LogStack_indent += '\t';
    }
    tempLogStack_indent = LogStack_indent;

    tempContext = Context;
    templogRefNum = logRefNum++;
    // templogRefNum = logRefNum;
    logMessage = build_log("\t> Opened: " + Context);
    // Serial.println("!ok");
    // logMessage = tempLogStack_indent + "log#" + String(logIncNum++) + "\tRef#" + String(templogRefNum) + "\tTime = " + String(logTime) + ;
    SerialLogger.println(logMessage);
    // Serial.println("~Constructed!");
}
SystemLogger::~SystemLogger()
{
    // Serial.println("~destructing!");
    logStack--;

    logMessage = build_log("\t> Closed: " + tempContext);
    SerialLogger.println(logMessage);

    // Serial.println("~destructed!");
    // logMessage_push = "";
    // logTime = millis() / __logTimePrescaler;
    // logMessage = tempLogStack_indent + "log#" + String(logIncNum++) + "\tRef#" + String(templogRefNum) + "\tTime = " + String(logTime) + "\t> Closed: " + tempContext;
    // SerialLogger.println(logMessage);
}

void SystemLogger::push_log()
{
    // build_log(logMessage_push);
    // Serial.println("~pushing!");
    SerialLogger.print(logMessage_push);
    logMessage_push = "";
}
void SystemLogger::add_log(String log_message)
{
    // Serial.println("~Adding");
    // Serial.println("~logMessage_push before: " + logMessage_push);
    String tempString = ">" + build_log("\t> " + log_message) + "\n";
    logMessage_push += tempString;

    // Serial.println("~logMessage_push after: " + logMessage_push);
    // Serial.println("~Added");
}
String SystemLogger::build_log(String _log_string)
{
    String temp_logMessage;
    // Serial.println("~Building");
    logTime = millis() / __logTimePrescaler;

    temp_logMessage =
        tempLogStack_indent +
        ">log#" + String(logIncNum++) +
        "\tRef#" + String(templogRefNum) +
        "\tTime = " + String(logTime) +
        _log_string;

    // Serial.println("~temp_logMessage: "+ temp_logMessage);
    // Serial.println("~Built");
    return temp_logMessage;
}
uint32_t SystemLogger::logRefNum = 0;
uint32_t SystemLogger::logIncNum = 0;
uint8_t SystemLogger::logStack = 0;