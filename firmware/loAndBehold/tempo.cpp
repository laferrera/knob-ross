#include "tempo.h"
#include "globals.h"

float globalBPM = 120.0f;

float Tempo::getBPM(){
  return globalBPM;
  // return 60000.0 / beatLengthMS;
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
}
