#include "Arduino.h"

// #include <vector>
#define __logTimePrescaler_ms 1
#define __logTimePrescaler_fs 10
#define __logTimePrescaler_s 1000

#define __logTimePrescaler __logTimePrescaler_s

class SystemLogger
{
public:
    SystemLogger(String Context);
    ~SystemLogger();
    void push_log();
    void add_log(String log_message);

private:
    // vector<String> logMessages;  //Todo: enable this when using SD card logger

    String build_log(String _log_string);

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