#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H

#include <Bounce2.h>
#include <Encoder.h>
#include "graph.h"
#include "channel.h"

float channelAccumulator[] = {0,0,0,0,0,0,0,0};
int channelScaler[] = {0,0,0,0,0,0,0,0};
float prevChannelAccumulator[] = {0,0,0,0,0,0,0,0};
float graphs[NUM_OF_CHANNELS][SCREEN_WIDTH];


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
Encoder *encoders[12] = {&enc1, &enc2, &enc3, &enc4, &enc5, &enc6, &enc7, &enc8, &enc9, &enc10, &enc11, &enc12};
int controlChannelValue = 0;
int buttonCancelPin = 3; 
int buttonOkayPin = 7;
Button buttonCancel = Button();
Button buttonOkay = Button();

// String encoderDestinations[] = {"AMP", "FREQ", "WAVEFORM", "OFFSET"};


// std::queue<float> graphQueues[NUM_OF_CHANNELS][128]; 
// std::array<std::queue<float>, NUM_OF_CHANNELS> graphQueues;
// std::array<FixedQueue<float, SCREEN_WIDTH>, NUM_OF_CHANNELS> graphQueues;

// TODO - make these into vector


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

