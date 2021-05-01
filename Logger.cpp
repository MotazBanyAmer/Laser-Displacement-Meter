#include "Logger.h"
#include "appConfig.h"
#define SerialLogger SerialDebug

SystemLogger::SystemLogger(String Context) //:tempContext(Context), templogRefNum(logRefNum)
{
    templogStack = ++logStack;
    for (int i = 1; i < templogStack; i++)
    {
        LogStack_indent += '\t';
    }
    tempLogStack_indent = LogStack_indent;
    logTime = millis() / __logTimePrescaler;
    tempContext = Context;
    templogRefNum = logRefNum;
    // templogRefNum = logRefNum;
    logMessage = LogStack_indent + "log#" + String(logIncNum++) + "\tRef#" + String(logRefNum++) + "\tTime = " + String(logTime) + "\t> Opened: " + Context;
    SerialLogger.println(logMessage);
}
SystemLogger::~SystemLogger()
{
    logStack--;

    logTime = millis() / __logTimePrescaler;
    logMessage = tempLogStack_indent + "log#" + String(logIncNum++) + "\tRef#" + String(templogRefNum) + "\tTime = " + String(logTime) + "\t> Closed: " + tempContext;
    SerialLogger.println(logMessage);
}
uint32_t SystemLogger::logRefNum = 0;
uint32_t SystemLogger::logIncNum = 0;
uint8_t SystemLogger::logStack = 0;