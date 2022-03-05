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
  int phase;
  int minValue;
  uint8_t maxValue;
  bool lfoEnabled;
  int offset;
  uint8_t lfoType;
  uint8_t knobDestination;
  uint8_t lfoDestination;
};

struct Knob knob1;
struct Knob knob2;
struct Knob knob3;
struct Knob knob4;
struct Knob knob5;
struct Knob knob6;
struct Knob knob7;
struct Knob knob8;
struct Knob knob9;
struct Knob knob10;
struct Knob knob11;
struct Knob knob12;
struct Knob knob13;
struct Knob knob14;
struct Knob knob15;
struct Knob knob16;

Encoder *encoders[17] = {&enc1, &enc2, &enc3, &enc4, &enc5, &enc6, &enc7, &enc8, &enc9, &enc10, &enc11, &enc12, &enc13, &enc14, &enc15, &enc16};
Knob *knobs[16] = {&knob1, &knob2, &knob3, &knob4, &knob5, &knob6, &knob7, &knob8, &knob9, &knob10, &knob11, &knob12, &knob13, &knob14, &knob15, &knob16};

void initializeKnobs(void){
  // initiaize knobs, should probably do this for banks.
  for (int i = 0; i < 16; i++) {
    Knob knob;
    knob.value = 0;
    knob.cc = 102 + i;
    knob.phase = 0;
    knob.lfoEnabled = false;
    knob.lfoType = 0;
    knob.minValue = 0;
    knob.maxValue = 127;
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

