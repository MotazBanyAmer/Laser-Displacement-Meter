#ifndef __APP_COMMON_H__
#define __APP_COMMON_H__

#include "Arduino.h"

boolean checkRespText(String *str, String resp);

inline String JSONResp_value = " "; //TODO: Review[JSON]
inline String JSONResp_id = " "; //TODO: Review[JSON]

void initProject();
void startup_actions();

#endif