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

struct Knob {
  int value;
  uint8_t cc;
  int minValue;
  uint8_t maxValue;
  int phase;
  bool lfoEnabled;
  uint8_t lfoWave;
  float lfoAmp;
  bool lfoFreqBPM;
  int lfoFreq;
  int lfoFreqNoteValue; // bar, 1/2, 1/4, 1/8, 1/16, 1/32, 1/64, 1/128
  uint8_t lfoFreqNoteValueAmount; // 1-16 1/4 notes.... 
  int offset;
  Knob* knobDestination;
  uint8_t lfoDestination;
  // lfo amp
  // lfo freq 
  // lfo param? i.e. pulsewidth
  // lfo time offset - is this the same as phase
};

struct Knob knob1, knob2, knob3, knob4, knob5, knob6, knob7, knob8, knob9, knob10, knob11, knob12, knob13, knob14, knob15, knob16;

Encoder *encoders[17] = {&enc1, &enc2, &enc3, &enc4, &enc5, &enc6, &enc7, &enc8, &enc9, &enc10, &enc11, &enc12, &enc13, &enc14, &enc15, &enc16};
Knob *knobs[16] = {&knob1, &knob2, &knob3, &knob4, &knob5, &knob6, &knob7, &knob8, &knob9, &knob10, &knob11, &knob12, &knob13, &knob14, &knob15, &knob16};
String lfoDestination[] = {"FREQ", "AMP", "PHASE", "OFFSET"};

void initializeKnobs(void){
  // initiaize knobs, should probably do this for banks.
  for (int i = 0; i < 16; i++) {
    Knob knob;
    knob.value = 0;
    knob.cc = 102 + i;
    knob.minValue = 0;
    knob.maxValue = 127;
    knob.phase = 0;
    knob.lfoEnabled = false;
    knob.lfoWave = 0;
    knob.offset = 0;
    knob.knobDestination = 0;
    knob.lfoDestination = 0;
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

