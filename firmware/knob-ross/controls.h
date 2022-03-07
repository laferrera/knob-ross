#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H

#include <Bounce2.h>
#include <Encoder.h>

bool knobsDirty = false;
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
// Encoder controlKnob(15, 16);
Encoder controlKnob(0, 1);
int controlKnobValue = 0;
int buttonCancelPin = 6; 
int buttonOkayPin = 12;
Button buttonCancel = Button();
Button buttonOkay = Button();


//maybe lets call this a channel
struct Knob {
  int output_value; // 0 - 127 for midi
  int encoder_value; // -infinity to +infinity
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
  uint8_t encoderDestination; // i.e. knob controls midi cc / lfo amp / lfo freq / lfo offset / wave
  Knob *knobDestination;      // which knob does the lfo control? 
  uint8_t lfoOutputDestination;  // which param on knob above does LFO control? amp / freq / offset / wave
  // lfo param? i.e. pulsewidth
};

struct Knob knob1, knob2, knob3, knob4, knob5, knob6, knob7, knob8, knob9, knob10, knob11, knob12, knob13, knob14, knob15, knob16;

Encoder *encoders[17] = {&enc1, &enc2, &enc3, &enc4, &enc5, &enc6, &enc7, &enc8, &enc9, &enc10, &enc11, &enc12, &enc13, &enc14, &enc15, &enc16};
Knob *knobs[16] = {&knob1, &knob2, &knob3, &knob4, &knob5, &knob6, &knob7, &knob8, &knob9, &knob10, &knob11, &knob12, &knob13, &knob14, &knob15, &knob16};
String lfoDestination[] = {"FREQ", "AMP", "PHASE", "OFFSET"};

void initializeKnobs(void){
  // initiaize knobs, should probably do this for banks.
  for (int i = 0; i < 16; i++) {
    Knob knob;
    knob.output_value = 0;
    knob.encoder_value = 0;
    knob.cc = 102 + i;
    knob.phase = 0;
    knob.lfoEnabled = false;
    knob.lfoWave = 0;
    knob.lfoAmpOffset = 0;
    knob.knobDestination = 0;
    *knobs[i] = knob;
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

