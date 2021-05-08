#ifndef __ERRORS_H__
#define __ERRORS_H__
#include "Arduino.h"
#include "appCommon.h"
#include "appConfig.h"

//#include "Callbacks.h"

//#resetFunc perform a software reset for the arduino
void (*resetFunc)(void) = 0;

//#functionCallback Prototype to handle functions callbacker
typedef void (*functionCallback_t)(void);


class Retry 
{
public:
// void retryFunction(functionCallback_t retry_function(void* object), uint8_t )
private:
};



inline bool startErrorRepeatFlag = 0; //!new, I think this should noe be here
inline bool errorTimerCounter = 0;    //!new, I think this should noe be here

inline uint8_t errorStatus = 0; //0: no error, 1: new error, 2: error continoues //TODO:review this, this should be as modern enum or namespace or defines!

#endif