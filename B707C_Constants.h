#ifndef __B707C_CONSTANTS_H__
#define __B707C_CONSTANTS_H__
#include "stdint.h"

enum class B707C_Commands:uint8_t
{
laserBeamON = 0x4F,    //'D'
laserBeamOFF = 0x43,    // 'M'
moduleStatus = 0x53     // 'F'
};

enum class B707C_dModes:char
{
AutoMode = 0x44,    //'D'
SlowMode = 0x4D,    // 'M'
FastMode = 0x46     // 'F'
};

#define dataHeaderByte ':'
#define statHeaderByte ','

#define timeoutTrials 3
#define errorTrials 3

#endif