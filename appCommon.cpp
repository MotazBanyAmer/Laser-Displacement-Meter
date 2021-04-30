#include "appCommon.h"
boolean checkRespText(String *str, String resp)
{
  if (str->indexOf(resp) != -1) return 1;
  else return 0;
}