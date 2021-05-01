#include "B707C.h"
#include "Arduino.h"

double B707C::getDistance()
{
    if (LaserRcv.charAt(3) != 0x20) //change all of this to using indexOf (maybe index of "M: ") so index will be indexof text + shift
        return (double)(LaserRcv.charAt(3) - 0x30) * 10.0 + (double)(LaserRcv.charAt(4) - 0x30) * 1.0 + (double)(LaserRcv.charAt(6) - 0x30) * 0.1 + (double)(LaserRcv.charAt(7) - 0x30) * 0.01 + (double)(LaserRcv.charAt(8) - 0x30) * 0.001;
    if (LaserRcv.charAt(3) == 0x20)
        return (double)(LaserRcv.charAt(4) - 0x30) * 1.0 + (double)(LaserRcv.charAt(6) - 0x30) * 0.1 + (double)(LaserRcv.charAt(7) - 0x30) * 0.01 + (double)(LaserRcv.charAt(8) - 0x30) * 0.001;
}
void B707C::waitResp_Dist() {
  doneLaser = 0;
  errorLaser = 0;
  msgEnd = 0;
  LaserRcv = " ";
  rcvChar = ' ';
  while (!doneLaser)
  {
    while (SerialLaser.available())
    {
      rcvChar = SerialLaser.read();
      if (rcvChar != 0xFFFFFFFE)
      {
        LaserRcv += rcvChar;
        if (rcvChar == 0x0A) {
          msgEnd = 1;
        }
      }
    }
    if (msgEnd && checkRespText(&LaserRcv, "m,"))
    {
      Serial.println("Laser OK");
      doneLaser = 1;
      errorLaser = 0;
    }
    if (msgEnd && checkRespText(&LaserRcv, "Er"))
    {
      Serial.println("Laser Bad");
      doneLaser = 1;
      errorLaser = 1;
    }
  }
}
void B707C::waitResp_Temp()
{
    doneLaser = 0;
    errorLaser = 0;
    msgEnd = 0;
    LaserRcv = " ";
    rcvChar = ' ';
    while (!doneLaser)
    {
        while (SerialLaser.available())
        {
            rcvChar = SerialLaser.read();
            if (rcvChar != 0xFFFFFFFE)
            {
                LaserRcv += rcvChar;
                if (rcvChar == 0x0A)
                {
                    msgEnd = 1;
                }
            }
        }
        if (msgEnd && checkRespText(&LaserRcv, "C,"))
        {
            Serial.println("Temp OK");
            Serial.println(LaserRcv);
            doneLaser = 1;
            errorLaser = 0;
        }
        if (msgEnd && checkRespText(&LaserRcv, "Er"))
        {
            Serial.println("Temp Bad");
            doneLaser = 1;
            errorLaser = 1;
        }
    }
}

int B707C::getSignalQuality()
{
    int SQ = (LaserRcv.substring(11, 15)).toInt();
    return SQ;
}
void B707C::printSQ()
{
    //##
}
double B707C::getTemp()
{
    int temp1 = LaserRcv.indexOf("S");
    return (double)(LaserRcv.charAt(temp1 + 3) - 0x30) * 10.0 + (double)(LaserRcv.charAt(temp1 + 4) - 0x30) * 1.0 + (double)(LaserRcv.charAt(temp1 + 6) - 0x30) * 0.1;
}
double B707C::getVlt()
{
    return (double)(LaserRcv.charAt(10) - 0x30) * 1.0 + (double)(LaserRcv.charAt(12) - 0x30) * 0.1;
}
void B707C::getError()
{
    errorID = LaserRcv.charAt(4) - 0x30 * 10 + LaserRcv.charAt(5) - 0x30 * 1;
}

void B707C::printError()
{
    if (errorID == 1)
        Serial.println("Power Error");
    else if (errorID == 2)
        Serial.println("Internal Error");
    else if (errorID == 3)
        Serial.println("Low Temp!");
    else if (errorID == 4)
        Serial.println("High Temp!");
    else if (errorID == 5)
        Serial.println("Out of Range!");
    else if (errorID == 6)
        Serial.println("invalid Result!");
    else if (errorID == 7)
        Serial.println("Light too strong!");
    else if (errorID == 8)
        Serial.println("Weak Signal!");
    else if (errorID == 9)
        Serial.println("Strong Signal!");
    else if (errorID == 10)
        Serial.println("Hardware Fault 1");
    else if (errorID == 11)
        Serial.println("Hardware Fault 2");
    else if (errorID == 12)
        Serial.println("Hardware Fault 3");
}
void B707C::laserOn()
{
    SerialLaser.write(static_cast<uint8_t>(B707C_Commands::laserBeamON));
}
void B707C::laserOff()
{
    SerialLaser.write(static_cast<uint8_t>(B707C_Commands::laserBeamOFF));
}
void B707C::demandStatus()
{
    SerialLaser.write(static_cast<uint8_t>(B707C_Commands::moduleStatus));
}
void B707C::demandData(char msgID)
{
    SerialLaser.write(msgID);
}