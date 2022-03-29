#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H

#include <Bounce2.h>
#include <Encoder.h>
#include "lfo/oscillator.cpp"
#include "graph.h"

std::vector<daisysp::Oscillator> oscillators;

float channelAccumulator[] = {0,0,0,0,0,0,0,0};
int channelScaler[] = {0,0,0,0,0,0,0,0};
float prevChannelAccumulator[] = {0,0,0,0,0,0,0,0};

// Encoder enc1(0, 1);
Encoder enc1(24, 25);
Encoder enc2(28, 29);
Encoder enc3(30, 31);
Encoder enc4(0, 1);
Encoder enc5(39, 40);
Encoder enc6(39, 40);
Encoder enc7(39, 40);
// skip 13, cause that's led
Encoder enc8(39, 40);
Encoder enc9(39, 40);
Encoder enc10(39, 40);
Encoder enc11(39, 40);
Encoder enc12(39, 40);
Encoder enc13(39, 40);
Encoder enc14(39, 40);
Encoder enc15(39, 40);
Encoder enc16(39, 40);
// Encoder controlChannel(15, 16);
Encoder controlChannel(10, 11);
int controlChannelValue = 0;
int buttonCancelPin = 3; 
int buttonOkayPin = 7;
Button buttonCancel = Button();
Button buttonOkay = Button();

// String encoderDestinations[] = {"AMP", "FREQ", "WAVEFORM", "OFFSET"};

struct Channel {
  uint8_t index;
  float outputValue;            // -1 to 1
  long encoderValue;            // -infinity to +infinity
  int cc;                   // 102 -128 ?
  int phase;                    // i think this is -π to +π
  int clipMode;                    
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
  // Channel * channelDestination; // which channel does the lfo control?
  uint8_t outputDestination;    // which param on channel above does the channel control? value / amp / freq / offset / wave
  daisysp::Oscillator *lfo;
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
    // static daisysp::Oscillator *lfo = new daisysp::Oscillator;
    daisysp::Oscillator *lfo = new daisysp::Oscillator;
    oscillators.push_back(*lfo);
    // Serial.printf("Pointer lives at %p.\n", (void *)lfo);
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
    // channel.clipMode = CLIP_BOUNCE;
    channel.lfoFreq = 50.f;
    channel.lfoAmp = 0.75f;
    channel.lfoWave = i % 5;
    channel.lfoAmpOffset = 0;
    channel.channelDestinationIndex = i;
    // channel.channelDestination = &channel;
    channel.lfo = lfo;
    *channels[i] = channel;

    lfo->SetFreq(channel.lfoFreq);
    lfo->SetWaveform(channel.lfoWave);
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
    // channels[i]->outputValue = channels[i]->lfo->Process();
    // graphQueues[i].push(channels[i]->outputValue);

    float lfoOutput = channels[i]->lfo->Process();
    if (channels[i]->channelDestinationIndex == i) {
      channels[i]->outputValue = lfoOutput;
      // graphQueues[i].push(channels[i]->outputValue);
      channelAccumulator[i] += lfoOutput;
      channelAccumulator[i] += channels[i]->lfoAmpOffset;
      channelScaler[i] += 1;
    } else {
      int channelDestinationIndex = channels[i]->channelDestinationIndex;
      switch (channels[i]->outputDestination) {
        case OUT_BUS:
          channelAccumulator[channelDestinationIndex] += lfoOutput;
          channelScaler[channelDestinationIndex] += 1;
          break;
        case OUT_AMP:
          channels[channelDestinationIndex]->lfoAmp = lfoOutput;
          // channels[channelDestinationIndex]->lfo->SetAmp(channels[channelDestinationIndex]->lfoAmp);
          break;
        case OUT_FREQ:{
          float newfreq = (1.0f + lfoOutput) * channels[channelDestinationIndex]->lfoFreq;
          channels[channelDestinationIndex]->lfo->SetFreq(newfreq);
          break;
          }
        case OUT_WAVEFORM:
          channels[channelDestinationIndex]->lfoWave = (int)(lfoOutput * 10) % 7;
          // channels[channelDestinationIndex]->lfo->SetWaveform(channels[channelDestinationIndex]->lfoWave);
          break;
        case OUT_OFFSET:
          channels[channelDestinationIndex]->lfoAmpOffset = lfoOutput;
          break;
        default:
          // default is OUT_BUS
          channelAccumulator[channelDestinationIndex] += lfoOutput;
          channelScaler[channelDestinationIndex] += 1;
          break;
      }
    }
  }
  for (uint8_t i = 0; i < NUM_OF_CHANNELS; i++) {
    switch (channels[i]->clipMode){
      case CLIP_HARD:
        channelAccumulator[i] = fclamp(channelAccumulator[i], -1.0f, 1.0f);
        break;
      case CLIP_SCALE:
        channelAccumulator[i] *= 1.0f / channelScaler[i];
        channelAccumulator[i] = fclamp(channelAccumulator[i], -1.0f, 1.0f);
        break;
      case CLIP_BOUNCE:{
        while (channelAccumulator[i] > 1.0f || channelAccumulator[i] < -1.0f) {
          if (channelAccumulator[i] > 1.0f) {
            channelAccumulator[i] = 2.0f - channelAccumulator[i];
          } else if (channelAccumulator[i] < -1.0f) {
            channelAccumulator[i] = -2.0f - channelAccumulator[i];
          }
        }
        break;
      }
      default:
        // default is CLIP_HARD
        channelAccumulator[i] = fclamp(channelAccumulator[i], -1.0f, 1.0f);
        break;
    }
    channels[i]->outputValue = channelAccumulator[i];
    graphQueues[i].push(channels[i]->outputValue);
  }
  memset(channelAccumulator, 0, sizeof(channelAccumulator));
  memset(channelScaler, 0, sizeof(channelScaler));
}

#endif

