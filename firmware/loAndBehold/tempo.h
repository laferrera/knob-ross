#pragma once
#ifndef TEMPO_H
#define TEMPO_H

class Tempo
{
  public:
    static const int MAX_BEAT_LENGTH_MS = 2000; // 30.0bpm
    static const int MIN_TEMPO = 250; // 240.0bpm

    float getBPM(); // returns the number of beats per minute
    float setBPM(float bpm); // sets the number of beats per minute
    void setClickRate(int amount, int type);          // bar, 1/2, 1/4, 1/8, 1/16, 1/32, 1/64

    inline unsigned long getBeatLength() { return beatLengthMS; } // returns the length of the beat in milliseconds

  private:
    // config
    unsigned long maxBeatLengthMS = 2000; // 30.0bpm
    unsigned long minBeatLengthMS = 250; // 240.0bpm

    // timing
    unsigned long beatLengthMS = 500;

    // private methods
    void test_tap(unsigned long ms);

};


#endif