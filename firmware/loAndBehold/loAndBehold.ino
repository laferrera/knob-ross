#include <ArduinoTrace.h>
#include <Metro.h>
#include "display.h"
#include "controls.h"
#include "menu.h"
#include "lfo.h"

#define LED 13
int ledState = HIGH;
Metro ledMetro = Metro(250);

#define MIDI_CHANNEL 1

// unsigned long lastTimeDisplayMillis = millis();
elapsedMillis ellapsedDisplayMillis;
elapsedMillis ellaspedChannelCalcMillis;
// elapsedMillis ellapsedMidiSendMillis;
elapsedMillis ellapsedEncoderTouchMillis;
elapsedMillis ellapsedMetroMillis;
elapsedMicros ellapsedLfoMicros;

int curGraphIndex = 0;
bool graphHUD = false;

uint32_t screenStepTime = 6; // ~15fps
uint32_t channelCalcStepTime = 7;
// uint32_t midiSendStepTime = 13; 
uint32_t metroStepTime = 11; //
uint32_t lfoStepTime = 100;  // 100 microseconds is 10Âkhz

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

  startupScreen();
  initializeChannels();
  initializeButtons();
  // initializeGraphs();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, ledState);

  setupLfos();

  menu.init(); 
  setupChannelMenu(channels);
  setupMainMenu();
  menu.reInit();
  menu.drawMenu();
  screenDirty = true;
}

void loop() {
// always check buttons and encoders  
  buttonCancel.update();
  buttonOkay.update();



  if (buttonCancel.pressed()) {
    // menu.registerKeyPress(GEM_KEY_CANCEL);
    // screenDirty = true;
    if (curMode == PERFORMANCE){
      Serial.println("switching curMode to MAIN_MENU");
      curMode = MAIN_MENU;
      display.clearDisplay();
      menu.reInit();
      menu.drawMenu();
    } else {
      menu.registerKeyPress(GEM_KEY_CANCEL);
      screenDirty = true;
    }
  }

  if (buttonOkay.pressed()) {
    if (curMode == PERFORMANCE) {
      graphHUD = !graphHUD;
    } else {
      menu.registerKeyPress(GEM_KEY_OK);
      screenDirty = true;
    }
  }

  long newControlChannelValue = controlChannel.read();
  if ((newControlChannelValue != controlChannelValue) && (abs(newControlChannelValue - controlChannelValue) > 4)) {
  // if (newControlChannelValue != controlChannelValue) {
    if (curMode != PERFORMANCE) {
        if (newControlChannelValue > controlChannelValue) {
          menu.registerKeyPress(GEM_KEY_DOWN);
          screenDirty = true;
        } else {
          menu.registerKeyPress(GEM_KEY_UP);
          screenDirty = true;
        }
        controlChannelValue = newControlChannelValue;
    } else if (curMode == PERFORMANCE) {
      if (newControlChannelValue > controlChannelValue) {
        curGraphIndex = (curGraphIndex + 1) % NUM_OF_CHANNELS;
      } else {
        curGraphIndex = (curGraphIndex - 1) % NUM_OF_CHANNELS;
      }
        controlChannelValue = newControlChannelValue;
      }
  }

  // for (int i = 0; i < SIZE_OF_CHANNELS; i++) {
  //   long newChannelValue = encoders[i]->read();
  //   if (newChannelValue != channels[i]->encoder_value) {
  //     channelsDirty = true;
  //     ellapsedEncoderTouchMillis = 0;
  //     screenSaver = false;
  //     channels[i]->encoderValue = newChannelValue;
  //     usbMIDI.sendControlChange(channels[i]->cc, newChannelValue, MIDI_CHANNEL);
  //     ledState = HIGH;
  //     digitalWrite(LED, ledState);
  //     ledMetro.interval(250);
  //     String channeltext = "channel " + String(i + 1) + ": " + String(newChannelValue);
  //     // drawText(channeltext, 1);
  //     Serial.println(channeltext);
  //     // drawText(channeltext, 9 * (i + 2));
  //   }
  // }

  // screen cycle
  if (screenDirty && (ellapsedDisplayMillis > screenStepTime)) {
    // update display
    // Serial.println("updating display");
    ellapsedDisplayMillis = ellapsedDisplayMillis - screenStepTime;
    display.display();
  }

  // lfo cycle - do this at 10khz
  if (ellapsedLfoMicros > lfoStepTime) {
    ellapsedLfoMicros = ellapsedLfoMicros - lfoStepTime;
    processLfos();
  }

  if (ellaspedChannelCalcMillis > channelCalcStepTime) {
    if (curMode == PERFORMANCE) {
      drawGraph(curGraphIndex, graphHUD, channels[curGraphIndex]->lfoFreq);
    }
  }

  // metro cycle
  if (ellapsedMetroMillis > metroStepTime) {
    if (ledMetro.check() == 1) {
      ledState = LOW;
      digitalWrite(LED, ledState);
    }
    // update metro
    // Serial.println("metro stuff");
    ellapsedMetroMillis = ellapsedMetroMillis - metroStepTime;
  }

    // check for incoming midi messages

    // Menu draw
    // menu.drawMenu();

    // screensaver cycle
    // if (!screenSaver && (ellapsedEncoderTouchMillis > SCREEN_SAVER_TIMEOUT_MS)) {
    //   // update display
    //   screenSaver = true;
    //   display.fillScreen(SSD1306_BLACK);
    //   display.display();
    //   Serial.println("screensaver on ");
    // }

    if (curMode == MAIN_MENU) {
      //    menu.drawMenu();

    } else if (curMode == PERFORMANCE) {
      // drawing graph for channel 0
      

    } else if (curMode == CHANNEL) {
      // channelMenu.drawMenu();
      // screenDirty = true;
    } else if (curMode == TEMPO) {
      // tempoMenu.drawMenu();
      // screenDirty = true;
    }

    // if (CrashReport && Serial) {
    //   Serial.print(CrashReport);
    // }

    if (Serial.available()) {

      if (CrashReport) {
        Serial.print(CrashReport);
      }

      char ch = Serial.read();
      Serial.print(ch);
      if (ch) {
        ellapsedEncoderTouchMillis = 0;
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
      if (ch == 'p') {
        Serial.println("");
        for(int i = 0; i < NUM_OF_CHANNELS; i++){
          Serial.println("Channel :" + String(i));
          Serial.println("actual lfoFreq" + String(channels[i]->lfo->GetFreq()));
          Serial.println("lfoFreq: " + String(channels[i]->lfoFreq));
          Serial.println("lfoAmp: " + String(channels[i]->lfoAmp));
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
      if( ch == '0'){
        Serial.println("Trying to print the crash report");
        if (CrashReport) {
          Serial.print(CrashReport);
        }
      }
    }
  }
