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
    logMessage = build_log("\t> Opened: " + Context, __ntSubLog);
    // Serial.println("!ok");
    // logMessage = tempLogStack_indent + "log#" + String(logIncNum++) + "\tRef#" + String(templogRefNum) + "\tTime = " + String(logTime) + ;
    SerialLogger.println(logMessage);
    // Serial.println("~Constructed!");
}
SystemLogger::~SystemLogger()
{
    // Serial.println("~destructing!");
    logStack--;

    logMessage = build_log("\t> Closed: " + tempContext, __ntSubLog);
    SerialLogger.println(logMessage+"\n");

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
void SystemLogger::add_log_plain(String log_message)
{
    String tempString = build_log("\t> " + log_message, __isSubLog) + "\n";
    logMessage_push += tempString;
    //todo, maybe I will need to add counter
    //todo, meybe I will need to change the type string to array or vector of string
    //todo, maybe I will need to change the type from direct string to struct
    //same applies for add parameters
}
void SystemLogger::add_log_parameter(String log_message, uint32_t value)
{
    add_log_plain(log_message + ": " + String(value));
    // String tempString = ">" + build_log("\t> " + log_message + ) + "\n";
    // logMessage_push += tempString;
}
void SystemLogger::add_log_parameter(String log_message, double value, uint8_t prec)
{
    add_log_plain(log_message + ": " + String(value, prec));
    // String tempString = ">" + build_log("\t> " + log_message + String(value)) + "\n";
    // logMessage_push += tempString;
}
void SystemLogger::add_log_parameter(String log_message, String value)
{
    add_log_plain(log_message + ": " + String(value));
    // String tempString = ">" + build_log("\t> " + log_message + String(value)) + "\n";
    // logMessage_push += tempString;
}
String SystemLogger::build_log(String _log_string, bool subLog)
{
    String temp_logMessage;
    String temp_logHdr;

    logTime = millis() / __logTimePrescaler;
    if (subLog)
    {
        temp_logHdr = "|>log#";
    }
    else if (!subLog)
    {
        temp_logHdr = ">log#";
    }

    temp_logMessage =
        tempLogStack_indent +
        temp_logHdr + String(logIncNum++) +
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