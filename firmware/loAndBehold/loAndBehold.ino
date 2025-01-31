#include "globals.h"
#include <Metro.h>
#include <algorithm>
#include <iomanip>
#include "display.h"
#include "controls.h"
#include "tempo.h"
#include "menu.h"

#define LED 13
int encoderSens = 1;
int ledState = HIGH;
Metro ledMetro = Metro(250);
Tempo tempo;
modes curMode = MAIN_MENU;

#define MIDI_CHANNEL 1

// unsigned long lastTimeDisplayMillis = millis();
elapsedMillis ellapsedDisplayMillis;
elapsedMillis ellaspedChannelCalcMillis;
// elapsedMillis ellapsedMidiSendMillis;
elapsedMillis ellapsedTouchMillis;
elapsedMillis ellapsedMetroMillis;
elapsedMicros ellapsedLfoMicros;

int curGraphIndex = 0;
bool graphHUD = false;

uint32_t screenStepTime = 6; // ~15fps
uint32_t channelCalcStepTime = 36;
// uint32_t midiSendStepTime = 13; 
uint32_t metroStepTime = 11; //
uint32_t lfoStepTime = uint32_t(1000000.0f / SAMPLERATE);
// uint32_t lfoStepTime = uint32_t(100000.0f / SAMPLERATE);

void setup() {
  Serial.begin(38400);
  while (usbMIDI.read()) {
    // figure out what to do with midi clock....
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.setRotation(2);
  // TODO add startupscreenback
  // startupScreen();
  initializeChannels();
  initializeButtons();
  // initializeGraphs();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, ledState);

  // setupLfos();

  menu.init();
  setupMenus();
  menu.reInit(); // necessary?
  menu.drawMenu();
  screenDirty = true;
}

void loop() {
// always check buttons and encoders  
  buttonCancel.update();
  buttonOkay.update();

  if (buttonCancel.pressed()) {
    screenSaver = false;
    ellapsedTouchMillis = 0;
    // Serial.println("CANCEL");
    if (curMode == PERFORMANCE){
      Serial.println("switching curMode to MAIN_MENU");
      curMode = MAIN_MENU;
      display.clearDisplay();
      menu.reInit();
      menu.drawMenu();
      screenDirty = true;
    } else if (curMode == TAP_TEMPO){
      curMode = MAIN_MENU;
      display.clearDisplay();
      menu.reInit();
      menu.setMenuPageCurrent(tempoMenuPage);
      menu.drawMenu();
    } else if (curMode == MAIN_MENU) {
      if (menu.getMenuPageCurrent() == mainMenuStr) {
        setModeToPerformance();
      }
      menu.registerKeyPress(GEM_KEY_CANCEL);
      screenDirty = true;
    }
  }

  if (buttonOkay.pressed()) {
    screenSaver = false;
    ellapsedTouchMillis = 0;
    // Serial.println("OKAY");
    if (curMode == PERFORMANCE) {
      graphHUD = !graphHUD;
    } else if (curMode == TAP_TEMPO) {
      tempo.tap(true);
    } else if (curMode == MAIN_MENU) {
      menu.registerKeyPress(GEM_KEY_OK);
      screenDirty = true;
    }
  }


  // control encoder changes
  long newControlChannelValue = controlChannel.read();
  int encDelta = abs(newControlChannelValue - controlChannelValue);
  if ((newControlChannelValue != controlChannelValue) && (encDelta > encoderSens)) {
    screenSaver = false;
    ellapsedTouchMillis = 0;
    if (curMode == MAIN_MENU) {
        if (newControlChannelValue > controlChannelValue) {
          if(encDelta > (encoderSens * 2)){
            menu.registerKeyPress(GEM_KEY_BIG_DOWN);
          } else {
            menu.registerKeyPress(GEM_KEY_DOWN);
          }
          screenDirty = true;
        } else {
          if (encDelta > (encoderSens * 2)) {
            menu.registerKeyPress(GEM_KEY_BIG_UP);
          } else {
            menu.registerKeyPress(GEM_KEY_UP);
          }
          screenDirty = true;
        }
        controlChannelValue = newControlChannelValue;
    } else if (curMode == PERFORMANCE) {
      if (newControlChannelValue > controlChannelValue) {
        curGraphIndex = (curGraphIndex + 1) % NUM_OF_CHANNELS;
      } else {
        curGraphIndex = (curGraphIndex - 1) % NUM_OF_CHANNELS;
        if (curGraphIndex < 0) { curGraphIndex = NUM_OF_CHANNELS - 1;}
      }
    }
    controlChannelValue = newControlChannelValue;
  }


  // all the other encoder changes
  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    long newChannelValue = encoders[i]->read();
    if (newChannelValue != channels[i]->encoderValue) {
      long encoderDifference = newChannelValue - channels[i]->encoderValue;  
      channels[i]->encoderValue = newChannelValue;

      float newSetting = 0.0f;
      switch (channels[i]->encoderDestination){
        case ENC_AMP:
          newSetting = (0.01f * encoderDifference) + channels[i]->lfoAmp;
          newSetting = constrain(newSetting, -1.0f, 1.0f);
          // Serial.println("setting channel lfo amp to: " + String(newSetting));
          channels[i]->lfoAmp = newSetting;
          channels[i]->lfo->SetAmp(channels[i]->lfoAmp);
          break;
        case ENC_FREQ:
            // Todo: this works when going positive, but not when going negative
            if (encoderDifference > 0) {
              if (channels[i]->lfoFreq >= 10.0f) {
                newSetting = (1.f * encoderDifference) + floor(channels[i]->lfoFreq) + 0.0f;
              } else if (channels[i]->lfoFreq <= 0.01f) {
                newSetting = (0.001f * encoderDifference) + channels[i]->lfoFreq;
              } else if (channels[i]->lfoFreq <= 0.1f) {
                newSetting = (0.01f * encoderDifference) + channels[i]->lfoFreq;
              } else if (channels[i]->lfoFreq <= 10.f) {
                newSetting = (0.1f * encoderDifference) + channels[i]->lfoFreq;
              } 
            } else {
              if (channels[i]->lfoFreq >= 11.0f) {
                newSetting = (1.f * encoderDifference) + floor(channels[i]->lfoFreq) + 0.0f;
              } else if (channels[i]->lfoFreq <= 0.02f) {
                newSetting = (0.001f * encoderDifference) + channels[i]->lfoFreq;
              } else if (channels[i]->lfoFreq <= 0.2f) {
                newSetting = (0.01f * encoderDifference) + channels[i]->lfoFreq;
              } else if (channels[i]->lfoFreq <= 11.f) {
                newSetting = (0.1f * encoderDifference) + channels[i]->lfoFreq;
              }
            }
          newSetting = constrain(newSetting, .001f, 100.0f);
          channels[i]->lfoFreq = newSetting;
          channels[i]->lfo->SetFreq(channels[i]->lfoFreq);
          break;
        case ENC_OFFSET:
          newSetting = (0.01f * encoderDifference) + channels[i]->lfoAmpOffset;
          newSetting = constrain(newSetting, -1.0f, 1.0f);
          channels[i]->lfoAmpOffset = newSetting;
          break;
      }
      // usbMIDI.sendControlChange(channels[i]->cc, newChannelValue, MIDI_CHANNEL);
      ledState = HIGH;
      digitalWrite(LED, ledState);
      ledMetro.interval(250);
    }
  }

  // screen cycle
  if (screenDirty && !screenSaver && (ellapsedDisplayMillis > screenStepTime)) {
    if (curMode == MAIN_MENU) {
      // menu.drawMenu();
    } 
    display.display();
    screenDirty = false;
    ellapsedDisplayMillis = ellapsedDisplayMillis - screenStepTime;
  }

  // lfo cycle - do this at Samplerate -- 1 kHz = 1000 µs
  if (ellapsedLfoMicros > lfoStepTime) {
    // Serial.println("ellapsedLfoMicros: " + String(ellapsedLfoMicros));
    processLfos();
    ellapsedLfoMicros = ellapsedLfoMicros - lfoStepTime;
  }

  if (ellaspedChannelCalcMillis > channelCalcStepTime) {
    if (curMode == PERFORMANCE) {
      drawGraph(curGraphIndex, graphHUD, channels[curGraphIndex]->lfoFreq);
    }
    else if (curMode == TAP_TEMPO) {
      drawTapTempoScreen(tempo.getBPM());
    }
    ellaspedChannelCalcMillis = 0;
  }

  // metro cycle
  if (ellapsedMetroMillis > metroStepTime) {
    if (ledMetro.check() == 1) {
      ledState = LOW;
      digitalWrite(LED, ledState);
    }
    // update metro
    ellapsedMetroMillis = ellapsedMetroMillis - metroStepTime;
  }

    // check for incoming midi messages

    // screensaver cycle
    if (!screenSaver && (ellapsedTouchMillis > SCREEN_SAVER_TIMEOUT_MS)) {
      screenSaver = true;
      display.fillScreen(SSD1306_BLACK);
      display.display();
      Serial.println("screensaver on ");
    }    

    if (Serial.available()) {

      if (CrashReport) {
        Serial.print(CrashReport);
      }

      char ch = Serial.read();
      Serial.print(ch);
      if (ch) {
        ellapsedTouchMillis = 0;
      }
      if (ch == 'w') {
        menu.registerKeyPress(GEM_KEY_UP);
      }
      if (ch == 'a') {
        menu.registerKeyPress(GEM_KEY_LEFT);
      }
      if (ch == 'd') {
        menu.registerKeyPress(GEM_KEY_RIGHT);
      }
      if (ch == 's') {
        menu.registerKeyPress(GEM_KEY_DOWN);
      }
      if (ch == 'z') {
        menu.registerKeyPress(GEM_KEY_CANCEL);
        curMode = MAIN_MENU;
      }
      if (ch == 'c') {
        menu.registerKeyPress(GEM_KEY_OK);
      }
      if (ch == 't') {
        Serial.println("Tempo: " + String(tempo.getBPM()));
      }
      if (ch == 'p') {
        Serial.println("");
        for(int i = 0; i < NUM_OF_CHANNELS; i++){
          Serial.println("Channel :" + String(i));
          Serial.println("Output Value : " + String(channels[i]->outputValue));
          Serial.println("Encoder Destination : " + String(channels[i]->encoderDestination));
          Serial.println("Offset : " + String(channels[i]->lfoAmpOffset));
          Serial.println("Oscillator lfoFreq: " + String(channels[i]->lfo->GetFreq(), 3));
          Serial.println("Knob lfoFreq: " + String(channels[i]->lfoFreq, 3));
          Serial.println("Knob lfoAmp: " + String(channels[i]->lfoAmp));
          Serial.println("last graph val: " + String(graphQueues[i].back()));
        }
        Serial.println("channelAccumulator[1]" + String(channelAccumulator[1]));
      }
      if (ch == 'g') {
        Serial.println("Setting Channel 3 output to Channel 1 freq");
        channels[2]->channelDestinationIndex = 1;
        channels[2]->outputDestination = OUT_BUS;
      }
      if (ch == 'h') {
        Serial.println("Setting Channel 3 Amp to 0.95");
        channels[2]->lfoAmp = 0.95;
        channels[2]->lfo->SetAmp(channels[2]->lfoAmp);
        channels[2]->lfoFreq = 100.0f;;
        channels[2]->lfo->SetFreq(channels[2]->lfoFreq);
      }
      if (ch == 'j') {
        Serial.println("Setting Channel 3 Wave to Sqr");
        channels[2]->lfoWave = 5;
        channels[2]->lfo->SetWaveform(5);
      }
      if (ch == 'e' || ch == '.') {
        curMode = PERFORMANCE;
        curGraphIndex = (curGraphIndex + 1) % NUM_OF_CHANNELS;
        Serial.println("Current Graph Index: " + String(curGraphIndex));
      }
      if( ch == 'm'){
        Serial.println("Current menu is: " + String(menu.getMenuPageCurrent()));
      }
      if( ch == '0'){
        Serial.println("Trying to print the crash report");
        if (CrashReport) {
          Serial.print(CrashReport);
        }
      }
      if (ch == 'h') {
        bool hidden = hiddenMenuItem.getHidden();
        hiddenMenuItem.hide(!hidden);
        Serial.println("Hidden menu item is now hidden?: " + String(hiddenMenuItem.getHidden()));
        Serial.println("redrawing menu");
        menu.reInit();
        menu.drawMenu();
        display.display();
      }
    }
  }
