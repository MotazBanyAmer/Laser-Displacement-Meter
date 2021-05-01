#ifndef __DEVICE_MELODIES_H__
#define __DEVICE_MELODIES_H__


#define buzzerPin 43
#define shortTone1 90
#define shortTone2 125
#define shortTone3 200
#define midTone1 250
#define midTone2 300
#define longTone1 500
#define longTone2 500
#define longTone3 535
#define mult1 1.15
#define mult2 1.3

class deviceMelody
{
public:
    void generateMelody(int pitch[], int duration[], int melodyLength);
    void startMelody();
    void HTTPInitSucsMelody();

private:
    int noteDurations[8];
    int melody[8];
};

#endif