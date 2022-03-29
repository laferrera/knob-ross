#ifndef GLOBALS_H
#define GLOBALS_H

#define NUM_OF_CHANNELS 8
#define SAMPLERATE 10000.0f
// other defines go here

extern float globalBPM;
enum modes { MAIN_MENU, PERFORMANCE, CHANNEL, TAP_TEMPO, LEARN, GLOBAL, TWO_HEADED_MONSTER} ;
extern modes curMode;

#endif // GLOBALS_H
