#ifndef GLOBALS_H
#define GLOBALS_H

#define NUM_OF_CHANNELS 8
#define SAMPLERATE 500.0f
// freq = 1000000.0 / SAMPLERATE
// 10000µs for 100hz
// 2000µs for 500hz
// 1000µs for 1000hz
// 200µs for 5000hz

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

enum encoderDestinations {ENC_AMP, ENC_FREQ, ENC_OFFSET, ENC_BPM_NUM, ENC_BPM_DEN, ENC_WAVEFORM, ENC_PHASE};
enum outputDestinations {OUT_BUS, OUT_AMP, OUT_FREQ, OUT_WAVEFORM, OUT_OFFSET, OUT_MIDI};
enum clipMode {CLIP_HARD, CLIP_SCALE, CLIP_BOUNCE, CLIP_RECTIFY};
enum lfoShapes {LFO_NONE, LFO_SIN, LFO_TRI, LFO_SAW, LFO_RAMP,LFO_SQUARE, LFO_SMOOTH, LFO_RANDOM, LFO_CLOCK};
enum lfoFreqBeatModes {LFO_FREQ, LFO_BEAT};



#endif // GLOBALS_H
