#pragma once
#ifndef TEMPO_H
#define TEMPO_H

#include "src/ArduinoTapTempo/ArduinoTapTempo.h"


class Tempo
{
  public:
    // float globalBPM = 120.0f;

    static const int MAX_BEAT_LENGTH_MS = 2000; // 30.0bpm
    static const int MIN_TEMPO = 250; // 240.0bpm
  
    float getBPM(); // returns the number of beats per minute
    float setBPM(float bpm); // sets the number of beats per minute
    void setClickRate(int amount, int type);          // bar, 1/2, 1/4, 1/8, 1/16, 1/32, 1/64

    inline unsigned long getBeatLength() { return beatLengthMS; } // returns the length of the beat in milliseconds
    
    void tap(bool buttonDown);                                 // call this each time you read your button state, accepts a boolean indicating if the button is down

  private:
    // config
    unsigned long maxBeatLengthMS = 2000; // 30.0bpm
    unsigned long minBeatLengthMS = 250; // 240.0bpm

    // timing
    unsigned long beatLengthMS = 500;

    // private methods
    void test_tap(unsigned long ms);

    // tap tempo
    ArduinoTapTempo tapTempo;
};


#endif