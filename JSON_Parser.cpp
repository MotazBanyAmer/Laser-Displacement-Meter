#include "JSON_Parser.h"

String JSON_Parser::getNames()
{ /*String context1, String context2*/
    int temp1;
    int temp2;
    int temp3;
    String resultString;
    temp1 = tempMsg.indexOf(dqString);
    temp2 = 1; //context1.length();
    temp3 = tempMsg.indexOf(dqString, temp1 + temp2);
    //  Serial.println("temp1: " + String(temp1));
    //  Serial.println("temp2: " + String(temp2));
    //  Serial.println("temp3: " + String(temp3));
    //  Serial.println("result length: " + String(temp3 - (temp1 + temp2)));

    resultString = tempMsg.substring(temp1 + temp2, temp3);
    tempMsg.remove(0, temp3 + 1);
    return resultString;
}
String JSON_Parser::getValues(String context1, String context2)
{ /**/
    int temp1;
    int temp2;
    int temp3;
    String resultString;
    temp1 = tempMsg.indexOf(context1);
    temp2 = context1.length();
    temp3 = tempMsg.indexOf(context2, temp1 + temp2);
    //  Serial.println("temp1: " + String(temp1));
    //  Serial.println("temp2: " + String(temp2));
    //  Serial.println("temp3: " + String(temp3));
    //  Serial.println("result length: " + String(temp3 - (temp1 + temp2)));

    resultString = tempMsg.substring(temp1 + temp2, temp3);
    // Serial.print("(1) " + resultString + " - ");
    /*
    if (resultString.endsWith("\"}")) {
      resultString = tempMsg.substring(temp1 + temp2 + 1, temp3 - 1);
    }
  */
    if (resultString.startsWith(dqString))
    {
        resultString = tempMsg.substring(temp1 + temp2 + 1, temp3 - 1);
    }
    tempMsg.remove(0, temp3 + 1);
    return resultString;
}
byte JSON_Parser::getPairsCount()
{
    int i = 0;
    int arrCount = 0;
    int index;
    do
    {
        index = tempMsg.indexOf(",", i);
        i = index + 1;
        arrCount++;
    } while (index != -1);
    return arrCount;
}
void JSON_Parser::getAllJSON(String JSONobj)
{
    byte pairsCount;
    tempMsg = JSONobj;
    Serial.println("tempMsg: " + tempMsg);

    pairsCount = getPairsCount();
    Serial.println(pairsCount);

    for (int pairCounter = 0; pairCounter < pairsCount; pairCounter++)
    {
        //Serial.println("pairCounter: " + String(pairCounter));
        names[pairCounter] = getNames(); /*dqString, dqString*/
        Serial.print(names[pairCounter] + " : ");
        //Serial.println("tempMsg: " + tempMsg);

        if (pairCounter != pairsCount - 1)
            values[pairCounter] = getValues(colon, comma); /**/
        else
            values[pairCounter] = getValues(colon, "}"); /**/
        Serial.println(values[pairCounter]);
        //Serial.println("tempMsg: " + tempMsg);
    }
}
String JSON_Parser::getCertainString(String JSONobj, String searchName)
{
    int temp1;
    int temp2;
    int temp3;
    String resultString;
    temp1 = JSONobj.indexOf(searchName);
    temp2 = searchName.length() + 2;
    temp3 = JSONobj.indexOf(",", temp1);
    if (temp3 == -1)
        temp3 = JSONobj.indexOf("}");

    resultString = JSONobj.substring(temp1 + temp2, temp3);
    if (resultString.startsWith(dqString))
    {
        resultString = JSONobj.substring(temp1 + temp2 + 1, temp3 - 1);
    }
    /*
  Serial.println("temp1: " + String(temp1));
  Serial.println("temp2: " + String(temp2));
  Serial.println("temp3: " + String(temp3));
  Serial.println("result length: " + String(temp3 - (temp1 + temp2)));
  Serial.println(searchName +  + " - " + resultString);
  */
    return resultString;

    /*
    if (valyeType = __number) resultString = (searchName.substring()).toInt;
    if (valyeType = __largeNumber)resultString = (searchName.substring()).toInt;
    if (valyeType = __String) resultString = searchName.substring();
  */
}
long JSON_Parser::getCertainNumber(String JSONobj, String searchName)
{
    int temp1;
    int temp2;
    int temp3;
    long resultInt;
    temp1 = JSONobj.indexOf(searchName);
    temp2 = searchName.length() + 2;
    temp3 = JSONobj.indexOf(",", temp1);
    if (temp3 == -1)
        temp3 = JSONobj.indexOf("}");

    resultInt = (JSONobj.substring(temp1 + temp2, temp3)).toInt();
    /*
  Serial.println("temp1: " + String(temp1));
  Serial.println("temp2: " + String(temp2));
  Serial.println("temp3: " + String(temp3));
  Serial.println("result length: " + String(temp3 - (temp1 + temp2)));
  Serial.println(searchName +  + " - " + String(resultInt));
  */
    return resultInt;
}