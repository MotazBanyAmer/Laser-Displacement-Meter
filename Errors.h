#ifndef __ERRORS_H__
#define __ERRORS_H__

inline bool startErrorRepeatFlag = 0; //!new, I think this should noe be here
inline bool errorTimerCounter = 0;    //!new, I think this should noe be here

inline uint8_t errorStatus = 0; //0: no error, 1: new error, 2: error continoues //TODO:review this, this should be as modern enum or namespace or defines!

#endif