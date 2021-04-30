#include "B707C.h"

B707C Laser;
void setup()
{
    initProject(); //Initialize project
    startup_actions();

    // Laser.laserOn();
}

void loop()
{
    Laser.demandData(SlowMode_Byte);
    Laser.waitResp_Dist();
    // delay(1000);
    Serial.println(Laser.getDistance());
}
