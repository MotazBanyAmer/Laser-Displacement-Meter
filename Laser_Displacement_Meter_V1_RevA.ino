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
    Laser.demandData(static_cast<char>(B707C_dModes::SlowMode));
    Laser.waitResp_Dist();
    // delay(1000);
    Serial.println(Laser.getDistance());
}
