#include "appCommon.h"
#include "appConfig.h""
boolean checkRespText(String *str, String resp)
{
  if (str->indexOf(resp) != -1) return 1;
  else return 0;
}

void initProject()
{
  SerialDebug.begin(115200);
  SerialSIM.begin(115200);
  SerialBT.begin(115200);
  SerialLaser.begin(19200);

  SerialSIM.setTimeout(5);
  SerialLaser.setTimeout(5);

  // pinMode(buzzerPin, OUTPUT);

  // setupTimer(); //!important !new, commented for later
}
void startup_actions()
{
  //startup_melody(); //TODO enable this at the end!
  //startMelody();    //!One of these shall be deleted

  SerialDebug.println("Start");
}