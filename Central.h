#ifndef __CENTRAL_H__
#define __CENTRAL_H__

struct DataFlag
{
    boolean get_Console;
    boolean get_OpMode;
    boolean get_ReqTime;
    boolean Upd_Temperature;
    boolean Upd_Laser;
};
inline volatile DataFlag dataFlag;

struct Payload_Data {
    double distance = 0;   //* used in the main code
    int signalQuality = 0; //* used in the main code
};
inline struct Payload_Data payload_Data;

inline uint8_t dataFreq = 8; //TODO: I believe this should be moved

#endif