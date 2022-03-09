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

uint32_t screenStepTime = 6; // ~15fps
uint32_t channelCalcStepTime = 7;
// uint32_t midiSendStepTime = 13; 
uint32_t metroStepTime = 11; //
uint32_t lfoStepTime = 100;  // 100 microseconds is 10khz

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

  pinMode(LED, OUTPUT);
  digitalWrite(LED, ledState);

  setupLfos();

  menu.init(); 
  setupChannelMenu(channels);
  setupMainMenu();
  menu.drawMenu();
  screenDirty = true;
}

void loop() {
// always check buttons and encoders  

  buttonCancel.update();
  buttonOkay.update();
  if (buttonCancel.pressed()) {
    Serial.println("canceled");
    screenDirty = true;
  }
  if (buttonOkay.pressed()) {
    screenDirty = true;
    menu.registerKeyPress(GEM_KEY_OK);
  }

  long newControlChannelValue = controlChannel.read();
  if ((newControlChannelValue != controlChannelValue) && (abs(newControlChannelValue - controlChannelValue) > 4)) {
  // if (newControlChannelValue != controlChannelValue) {
    if (curMode != "PERFORMANCE") {
        if (newControlChannelValue > controlChannelValue) {
          menu.registerKeyPress(GEM_KEY_DOWN);
          screenDirty = true;
        } else {
          menu.registerKeyPress(GEM_KEY_UP);
          screenDirty = true;
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
    // // then do a calc cycle coupled with a midi send cycle...
    // // two loops
    // // first loop goes through all the channels in order and gets output value / destination and accumulates it in variable for each channel
    for (uint8_t i = 0; i < NUM_OF_CHANNELS; i++) {
      int channelOutputIndex = channels[i]->channelDestination->index;
    //   // gotta scale the value if other channels are touching the channel.value....
    //   // i..e if channel2.lfo out goes to channel1.value, the new max value is 2....
    //   // so maybe need a vector?
      channelAccumulator[channelOutputIndex] += channels[i]->outputValue;
      channelScaler[channelOutputIndex] += 1;
    }
    //   // second loop goes through accumulatied values
    for (uint8_t i = 0; i < NUM_OF_CHANNELS; i++) {
      if(channelAccumulator[i] != prevChannelAccumulator[i]){
        //   do calculcation on accums.channel1
        //     usbMIDI.sendControlChange(channels[i]->cc, channelAccumulator[i], MIDI_CHANNEL);
      }
    }
    // // prevChannelAccumulator = channelAccumulator;
    // std::copy(std::begin(channelAccumulator), std::end(channelAccumulator), std::begin(prevChannelAccumulator));

    // // reset the accumulator
    memset(channelAccumulator, 0, sizeof(channelAccumulator));
    memset(channelScaler, 0, sizeof(channelScaler));
    // // memset(myarray, 0, N * sizeof(*myarray)); // for heap-allocated arrays, where N is the number of elements
    // // std::fill(myarray, myarray + N, 0);
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

    if (curMode == "MAIN_MENU") {
      //    menu.drawMenu();

    } else if (curMode == "PERFORMANCE") {
      int i = 0;
      String channeltext = "channel " + String(i + 1) + ": " + String(channels[i]->encoderValue);
      drawText(channeltext, 1);
      String controlChannelText = "control channel :" + String(controlChannelValue);
      drawText(controlChannelText, 3);

    } else if (curMode == "KNOB") {
      // channelMenu.drawMenu();
      // screenDirty = true;
    } else if (curMode == "TEMPO") {
      // tempoMenu.drawMenu();
      // screenDirty = true;
    }

    if (Serial.available()) {
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
      }
      if (ch == 'c') {
        menu.registerKeyPress(GEM_KEY_OK);
      }
    }
  }
