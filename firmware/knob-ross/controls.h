#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H
#define NUM_OF_CHANNELS 8

#include <Bounce2.h>
#include <Encoder.h>
#include "lfo/oscillator.cpp"
#include "graph.h"

float samplerate = 10000.0f;
int channelAccumulator[] = {0,0,0,0,0,0,0,0};
int channelScaler[] = {0,0,0,0,0,0,0,0};
int prevChannelAccumulator[] = {0,0,0,0,0,0,0,0};

bool channelsDirty = false;
// Encoder enc1(0, 1);
Encoder enc1(15, 16);
Encoder enc2(2, 3);
Encoder enc3(4, 5);
Encoder enc4(6, 7);
Encoder enc5(8, 9);
Encoder enc6(10, 11);
Encoder enc7(12, 24);
// skip 13, cause that's led
Encoder enc8(25, 26);
Encoder enc9(27, 28);
Encoder enc10(29, 30);
Encoder enc11(31, 32);
Encoder enc12(33, 34);
Encoder enc13(35, 36);
Encoder enc14(37, 38);
Encoder enc15(39, 40);
Encoder enc16(41, 14);
// Encoder controlChannel(15, 16);
Encoder controlChannel(0, 1);
int controlChannelValue = 0;
int buttonCancelPin = 6; 
int buttonOkayPin = 12;
Button buttonCancel = Button();
Button buttonOkay = Button();

// String encoderDestinations[] = {"AMP", "FREQ", "WAVEFORM", "OFFSET"};
enum encoderDestinations {ENC_AMP, ENC_FREQ, ENC_WAVEFORM, ENC_OFFSET};
enum outputDestinations {OUT_MIDI, OUT_AMP, OUT_FREQ, OUT_WAVEFORM, OUT_OFFSET};
enum clipMode {CLIP_HARD, CLIP_SCALE, CLIP_RECTIFY};
struct Channel {
  uint8_t index;
  float outputValue;            // -1 to 1
  long encoderValue;            // -infinity to +infinity
  uint8_t cc;                   // 102 -128 ?
  int phase;                    // i think this is -π to +π
  int lfoWave;              // 0 - 6 for lfo wave
  float lfoAmp;                 // -1 to 1
  float lfoAmpOffset;           // -1 to 1 - this shifts the lfo output wave up or down
  bool lfoFreqBPM;              // true | false / either BPM or Hz
  float lfoFreq;                // hz 0.001 - 50hz..... 16 minutes to 20ms
  int lfoFreqBeatType;          // bar, 1/2, 1/4, 1/8, 1/16, 1/32, 1/64
  uint8_t lfoFreqBeatAmount;    // 1-32 beats
  int lfoFreqBeatOffset;        // 1/64 - 1/32 - 1/16 - 1/8 - 1/4 - 1/2 - look at this how Reason does this...
  int encoderDestination;   // i.e. channel controls value / lfo amp / lfo freq / lfo offset / wave
  int channelDestinationIndex; // which channel id does the lfo control?
  Channel * channelDestination; // which channel does the lfo control?
  uint8_t outputDestination;    // which param on channel above does the channel control? value / amp / freq / offset / wave
  daisysp::Oscillator * lfo;
  // lfo param? i.e. pulsewidth
};

struct Channel channel1, channel2, channel3, channel4, channel5, channel6, channel7, channel8, channel9, channel10, channel11, channel12, channel13, channel14, channel15, channel16;
float graphs[NUM_OF_CHANNELS][128];
// std::queue<float> graphQueues[NUM_OF_CHANNELS][128]; 
// std::array<std::queue<float>, NUM_OF_CHANNELS> graphQueues;
// std::array<FixedQueue<float, SCREEN_WIDTH>, NUM_OF_CHANNELS> graphQueues;

// TODO - make these into vector
Encoder *encoders[17] = {&enc1, &enc2, &enc3, &enc4, &enc5, &enc6, &enc7, &enc8, &enc9, &enc10, &enc11, &enc12, &enc13, &enc14, &enc15, &enc16};
Channel *channels[16] = {&channel1, &channel2, &channel3, &channel4, &channel5, &channel6, &channel7, &channel8, &channel9, &channel10, &channel11, &channel12, &channel13, &channel14, &channel15, &channel16};

void initializeChannels(void){
  // initiaize channels, should probably do this for banks.
  // encoderDestinations ec;
  // ec = AMP;

  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    static daisysp::Oscillator *lfo = new daisysp::Oscillator;
    lfo->Init(samplerate);
    Channel channel;
    channel.index = i;
    channel.outputValue = 0;
    channel.encoderValue = 0;
    channel.encoderDestination = ENC_AMP;
    channel.outputDestination = OUT_MIDI;
    channel.cc = 102 + i;
    channel.phase = 0;
    channel.lfoFreq = 1.0f;
    channel.lfoAmp = 0.5;
    channel.lfoWave = 0;
    channel.lfoAmpOffset = 0;
    channel.channelDestinationIndex = i;
    channel.channelDestination = &channel;
    channel.lfo = lfo;
    *channels[i] = channel;
    
  }
}


void initializeButtons(void){
  buttonCancel.attach(buttonCancelPin, INPUT_PULLUP);
  buttonOkay.attach(buttonOkayPin, INPUT_PULLUP);
  buttonCancel.interval(5);
  buttonOkay.interval(5);
  buttonCancel.setPressedState(LOW);
  buttonOkay.setPressedState(LOW);
}

// lfo1Out = lfo1.Process(channels[i].lfoWave, channels[i].lfoAmp, channels[i].lfoFreq, channels[i].lfoFreqBeatType, channels[i].lfoFreqBeatAmount, channels[i].lfoFreqBeatOffset);
void processLfos(void) {
  for (uint8_t i = 0; i < NUM_OF_CHANNELS; i++) {
    channels[i]->outputValue = channels[i]->lfo->Process();
    graphQueues[i].push(channels[i]->outputValue);
  }
}

#endif

