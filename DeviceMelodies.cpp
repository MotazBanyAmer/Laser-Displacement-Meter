#include "DeviceMelodies.h"
#include "Arduino.h"
#include "pitches.h"

void deviceMelody::startMelody()
{
    //tone(buzzerPin,  NOTE_C6  , longTone3);
    //delay(longTone3 * mult1);
    melody[0] = NOTE_C6;
    noteDurations[0] = midTone1;
    melody[1] = NOTE_C6;
    noteDurations[1] = midTone1;
    generateMelody(melody, noteDurations, 2);
    delay(45);

    melody[0] = NOTE_E6;
    noteDurations[0] = shortTone1;
    melody[1] = NOTE_F6;
    noteDurations[1] = shortTone1;
    melody[2] = NOTE_G6;
    noteDurations[2] = shortTone1;
    generateMelody(melody, noteDurations, 3);
    generateMelody(melody, noteDurations, 3);

    noteDurations[2] = midTone2;
    generateMelody(melody, noteDurations, 3);
}

void deviceMelody::generateMelody(int pitch[], int duration[], int melodyLength)
{
    for (int thisNote = 0; thisNote < melodyLength; thisNote++)
    {
        tone(buzzerPin, pitch[thisNote], duration);
        delay(duration[thisNote] * mult1);
        noTone(buzzerPin);
    }
}
void deviceMelody::startup_melody()
{
  tone(buzzerPin, NOTE_C6, shortTone3);
  delay(shortTone3 * mult1);
  tone(buzzerPin, NOTE_C6, shortTone3);
  delay(shortTone3 * mult1);
}
void deviceMelody::HTTPInitSucsMelody()
{
    melody[0] = NOTE_E6;
    noteDurations[0] = shortTone1;
    melody[1] = NOTE_F6;
    noteDurations[1] = shortTone1;
    generateMelody(melody, noteDurations, 2);
    generateMelody(melody, noteDurations, 2);
}
