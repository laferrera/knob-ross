#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H
#define NUM_OF_CHANNELS 8

#include <Bounce2.h>
#include <Encoder.h>

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


//maybe lets call this a channel
struct Channel {
  uint8_t index;
  uint8_t outputValue; // 0 - 127 for midi
  long encoderValue; // -infinity to +infinity
  uint8_t cc; // 102 -128 ?
  int phase; // i think this is -π to +π
  bool lfoEnabled; // true | false 
  uint8_t lfoWave; // 0 - 6 for lfo wave
  float lfoAmp; // -1 to 1
  float lfoAmpOffset; // -1 to 1 - this shifts the lfo output wave up
  bool lfoFreqBPM; // true | false / either BPM or Hz
  float lfoFreq;   // hz .0005 - 50hz..... 33.333333333 minutes to 20ms
  int lfoFreqBeatType; // bar, 1/2, 1/4, 1/8, 1/16, 1/32, 1/64
  uint8_t lfoFreqBeatAmount; // 1-32 beats
  int lfoFreqBeatOffset;     // 1/64 - 1/32 - 1/16 - 1/8 - 1/4 - 1/2 - look at this how Reason does this...
  uint8_t encoderDestination; // i.e. channel controls value / lfo amp / lfo freq / lfo offset / wave
  Channel *channelDestination;      // which channel does the lfo control? 
  uint8_t outputDestination;  // which param on channel above does the channel control? value / amp / freq / offset / wave
  // lfo param? i.e. pulsewidth
};

struct Channel channel1, channel2, channel3, channel4, channel5, channel6, channel7, channel8, channel9, channel10, channel11, channel12, channel13, channel14, channel15, channel16;

Encoder *encoders[17] = {&enc1, &enc2, &enc3, &enc4, &enc5, &enc6, &enc7, &enc8, &enc9, &enc10, &enc11, &enc12, &enc13, &enc14, &enc15, &enc16};
Channel *channels[16] = {&channel1, &channel2, &channel3, &channel4, &channel5, &channel6, &channel7, &channel8, &channel9, &channel10, &channel11, &channel12, &channel13, &channel14, &channel15, &channel16};
String lfoDestination[] = {"FREQ", "AMP", "PHASE", "OFFSET"};

void initializeChannels(void){
  // initiaize channels, should probably do this for banks.
  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    Channel channel;
    channel.index = i;
    channel.outputValue = 0;
    channel.encoderValue = 0;
    channel.cc = 102 + i;
    channel.phase = 0;
    channel.lfoEnabled = false;
    channel.lfoWave = 0;
    channel.lfoAmpOffset = 0;
    channel.channelDestination = &channel;
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




#endif

