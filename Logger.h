#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "Arduino.h"

// #include <vector>
#define __logTimePrescaler_ms 1
#define __logTimePrescaler_fs 10
#define __logTimePrescaler_s 1000

#define __logTimePrescaler __logTimePrescaler_s

#define __isSubLog 1
#define __ntSubLog 0

class SystemLogger
{
public:
    SystemLogger(String Context);
    ~SystemLogger();
    void push_log();
    void add_log_plain(String log_message);
    void add_log_parameter(String log_message, uint32_t value);
    void add_log_parameter(String log_message, double value,uint8_t prec);
    void add_log_parameter(String log_message, String value);

private:
    // vector<String> logMessages;  //Todo: enable this when using SD card logger

    String build_log(String _log_string,bool subLog);

    String logMessage_push;


    String logMessage;
    uint32_t logTime;
    static uint32_t logRefNum;
    static uint32_t logIncNum;
    static uint8_t logStack; //level to indent

    String LogStack_indent = "";

    String debug_msg;

    //! static level, to indent log, to know what happens inside what
    // uint8_t logTimePrescaler

    String tempContext;
    String templogRefNum;
    uint8_t templogStack;
    String tempLogStack_indent = "";
};
#endif