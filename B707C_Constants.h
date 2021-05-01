#ifndef __B707C_CONSTANTS_H__
#define __B707C_CONSTANTS_H__
#include "stdint.h"

// #define laserBeamON_Byte    0x4F // 'O'
// #define laserBeamOFF_Byte   0x43 // 'C'
// #define moduleStatus_Byte   0x53 // 'S'
enum class B707C_Commands:uint8_t
{
laserBeamON = 0x4F,    //'D'
laserBeamOFF = 0x43,    // 'M'
moduleStatus = 0x53     // 'F'
};
// #define AutoMode_Byte   0x44 // 'D'
// #define SlowMode_Byte   0x4D // 'M'
// #define FastMode_Byte   0x46 // 'F'
enum class B707C_dModes
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