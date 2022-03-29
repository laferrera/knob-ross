#include "tempo.h"

float Tempo::getBPM(){
  return 60000.0 / beatLengthMS;
}

float Tempo::setBPM(float bpm){
  globalBPM = bpm;
  beatLengthMS = 60000 / bpm;
  return beatLengthMS;
}

void Tempo::tap(bool buttonDown){
  if(buttonDown){
    tapTempo.update(buttonDown);
  }
  setBPM(tapTempo.getBPM());
  // Serial.print("len:");
  // Serial.print(tapTempo.getBeatLength());
  // Serial.print(",\tbpm: ");
  // Serial.print(tapTempo.getBPM());
  // Serial.print(",\tchain active: ");
  // Serial.print(tapTempo.isChainActive() ? "yes" : "no ");
  // Serial.print(",\tlasttap: ");
  // Serial.print(tapTempo.getLastTapTime());
  // Serial.print(",\tprogress: ");
  // Serial.print(tapTempo.beatProgress());
  // Serial.print(",\tbeat: ");
  // Serial.println(tapTempo.onBeat() ? "beat" : "    ");
}
