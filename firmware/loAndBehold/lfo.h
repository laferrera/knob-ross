#pragma once
#ifndef LFO_H
#define LFO_H
// #include "lfo/oscillator.cpp"

String lfoTypes[] = {"SIN", "TRI", "SAW", "RAMP","SQUARE", "SMOOTH", "RANDOM"};

// float samplerate = 10000.0f;

static daisysp::Oscillator lfo1, lfo2, lfo3, lfo4, lfo5, lfo6, lfo7, lfo8, lfo9, lfo10, lfo11, lfo12, lfo13, lfo14, lfo15, lfo16;
float lfo1Out, lfo2Out, lfo3Out, lfo4Out, lfo5Out, lfo6Out, lfo7Out, lfo8Out, lfo9Out, lfo10Out, lfo11Out, lfo12Out, lfo13Out, lfo14Out, lfo15Out, lfo16Out;

void setupLfos(){
    lfo1.Init(samplerate);
    lfo2.Init(samplerate);
    lfo3.Init(samplerate);
    lfo4.Init(samplerate);
}

void testProcessLfos(){
    lfo1Out = lfo1.Process();
    lfo2Out = lfo2.Process();
    lfo3Out = lfo3.Process();
    lfo4Out = lfo4.Process();
    // Serial.println("LFO1: " + String(lfo1Out));
    // Serial.println("LFO2: " + String(lfo2Out));
    // Serial.println("LFO3: " + String(lfo3Out));
    // Serial.println("LFO4: " + String(lfo4Out));
}

#endif