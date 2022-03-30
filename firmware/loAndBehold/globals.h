#ifndef GLOBALS_H
#define GLOBALS_H

#define NUM_OF_CHANNELS 8
// #define SAMPLERATE 10000.0f
#define SAMPLERATE 100.0f
#define NUM_OF_CHANNELS 8
#define SCREEN_SAVER_TIMEOUT_MS 200000
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define FREQ_MIN 0
#define FREQ_MAX 30
#define BPM_MIN 1
#define BPM_MAX 300



extern float globalBPM;
enum modes { MAIN_MENU, PERFORMANCE, CHANNEL, TAP_TEMPO, LEARN, GLOBAL, TWO_HEADED_MONSTER} ;
extern modes curMode;
extern bool screenDirty;

enum encoderDestinations {ENC_AMP, ENC_FREQ, ENC_WAVEFORM, ENC_OFFSET};
enum outputDestinations {OUT_BUS, OUT_AMP, OUT_FREQ, OUT_WAVEFORM, OUT_OFFSET, OUT_MIDI};
enum clipMode {CLIP_HARD, CLIP_SCALE, CLIP_BOUNCE, CLIP_RECTIFY};
enum lfoShapes {LFO_NONE, LFO_SIN, LFO_TRI, LFO_SAW, LFO_RAMP,LFO_SQUARE, LFO_SMOOTH, LFO_RANDOM, LFO_CLOCK};
enum lfoFreqBeatModes {LFO_FREQ, LFO_BEAT};



#endif // GLOBALS_H
