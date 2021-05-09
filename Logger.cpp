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
    logMessage = build_log("Opened: " + Context, __ntSubLog);
    // Serial.println("!ok");
    // logMessage = tempLogStack_indent + "log#" + String(logIncNum++) + "\tRef#" + String(templogRefNum) + "\tTime = " + String(logTime) + ;
    SerialLogger.println(logMessage);
    // Serial.println("~Constructed!");
}
SystemLogger::~SystemLogger()
{
    // Serial.println("~destructing!");
    logStack--;

    logMessage = build_log("Closed: " + tempContext, __ntSubLog);
    SerialLogger.println(logMessage + "\n");

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
void SystemLogger::add_log_plain(String log_message, bool quick = 0)
{
    String tempString = build_log(log_message, __isSubLog) + "\n";
    // logMessage_push += tempString;
    if (!quick)
    {
        logMessage_push += tempString;
    }
    else
    {
        // push_log(tempString);
        SerialLogger.print(tempString);
    }

    //todo, maybe I will need to add counter
    //todo, meybe I will need to change the type string to array or vector of string
    //todo, maybe I will need to change the type from direct string to struct
    //same applies for add parameters
}
void SystemLogger::add_log_parameter(String log_message, uint32_t value, bool quick = 0)
{
    add_log_plain(log_message + ": " + String(value));
}
void SystemLogger::add_log_parameter(String log_message, double value, uint8_t prec, bool quick = 0)
{
    add_log_plain(log_message + ": " + String(value, prec), quick);
    // String tempString = ">" + build_log("\t> " + log_message + String(value)) + "\n";
    // logMessage_push += tempString;
}
void SystemLogger::add_log_parameter(String log_message, String value, bool quick = 0)
{
    add_log_plain(log_message + ": " + String(value), quick);
    // String tempString = ">" + build_log("\t> " + log_message + String(value)) + "\n";
    // logMessage_push += tempString;
}

void SystemLogger::add_microLog_plain(String log_message, bool quick = 0)
{
    String tempString = build_uLog(log_message) + "\n";
    if (!quick)
    {
        logMessage_push += tempString;
    }
    else
    {
        // push_log(tempString);
        SerialLogger.print(tempString);
    }
}
void SystemLogger::add_microLog_parameter(String log_message, uint32_t value, bool quick = 0)
{
    add_microLog_plain(log_message + String(value), quick);
}
void SystemLogger::add_microLog_parameter(String log_message, double value, uint8_t prec, bool quick = 0)
{
    add_microLog_plain(log_message + String(value, prec), quick);
}

String SystemLogger::build_log(String _log_string, bool subLog)
{
    String temp_logMessage;
    String temp_logHdr;

    logTime = millis() / __logTimePrescaler;
    if (subLog)
    {
        temp_logHdr = "|> ";
    }
    else if (!subLog)
    {
        temp_logHdr = "~> ";
    }

    temp_logMessage =
        tempLogStack_indent +
        temp_logHdr + _log_string +
        "\t- Ref#" + String(templogRefNum) +
        " Time:" + String(logTime) +
        " log#" + String(logIncNum++);

    // Serial.println("~temp_logMessage: "+ temp_logMessage);
    // Serial.println("~Built");
    return temp_logMessage;
}

String SystemLogger::build_uLog(String _log_string)
{

    String temp_logMessage;
    String temp_logHdr = "|- ";

    temp_logMessage =
        tempLogStack_indent +
        temp_logHdr + _log_string;

    return temp_logMessage;
}
uint32_t SystemLogger::logRefNum = 0;
uint32_t SystemLogger::logIncNum = 0;
uint8_t SystemLogger::logStack = 0;