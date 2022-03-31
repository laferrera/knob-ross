#pragma once
#ifndef CHANNEL_H
#define CHANNEL_H
#include "lfo/oscillator.cpp"
#include "globals.h"

std::vector<daisysp::Oscillator> oscillators;

struct Channel {
  uint8_t index;
  float outputValue;      // -1 to 1
  long encoderValue;      // -infinity to +infinity
  int cc;                 // 102 -128 ?
  int phase;              // i think this is -π to +π
  int clipMode;           // hard clip, bounce, or scale
  int lfoWave;            // 0 - ? for lfo wave
  float lfoAmp;           // -1 to 1
  float lfoAmpOffset;     // -1 to 1 - this shifts the lfo output wave up or down
  int lfoFreqBPM;         // 0 | 1 / either BPM or Hz
  float lfoFreq;          // hz 0.001 - 50hz..... 16 minutes to 20ms
  int lfoBeatNumerator;   // 1-32 beats
  int lfoBeatDenominator; // bar, 1/2, 1/4, 1/8, 1/16, 1/32, 1/64

  int lfoFreqBeatOffset;       // 1/64 - 1/32 - 1/16 - 1/8 - 1/4 - 1/2 - look at this how Reason does this...
  int encoderDestination;      // i.e. knob controls value / lfo amp / lfo freq / lfo offset / wave
  int channelDestinationIndex; // which channel id does the lfo control?
  uint8_t outputDestination;   // which param on channel above does the channel bus control? value / amp / freq / offset / wave
  daisysp::Oscillator *lfo;
};

// TODO - make these into vectors
struct Channel channel1, channel2, channel3, channel4, channel5, channel6, channel7, channel8, channel9, channel10, channel11, channel12;
Channel *channels[12] = {&channel1, &channel2, &channel3, &channel4, &channel5, &channel6, &channel7, &channel8, &channel9, &channel10, &channel11, &channel12};

void initializeChannels(void) {

  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    // static daisysp::Oscillator *lfo = new daisysp::Oscillator;
    daisysp::Oscillator *lfo = new daisysp::Oscillator;
    oscillators.push_back(*lfo);
    lfo->Init(SAMPLERATE);
    Channel channel;
    channel.index = i;
    channel.outputValue = 0;
    channel.encoderValue = 0;
    channel.encoderDestination = ENC_FREQ;
    channel.outputDestination = OUT_MIDI;
    channel.cc = 102 + i;
    channel.phase = 0;
    channel.clipMode = CLIP_HARD;
    channel.lfoFreqBPM = LFO_FREQ;
    channel.lfoFreq = 0.5f + i * 0.9f;
    channel.lfoBeatNumerator = 1;
    channel.lfoBeatDenominator = 4;
    channel.lfoAmp = 0.75f;
    channel.lfoWave = i % 5 + 1;
    channel.lfoAmpOffset = 0;
    channel.channelDestinationIndex = i;
    channel.lfo = lfo;
    *channels[i] = channel;

    lfo->SetFreq(channel.lfoFreq);
    lfo->SetWaveform(channel.lfoWave);
  }
}

#endif