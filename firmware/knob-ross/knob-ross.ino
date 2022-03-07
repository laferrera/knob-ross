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
elapsedMillis ellapsedKnobTouchMillis;
elapsedMillis ellapsedMetroMillis;
// elapsedMillis ellapsedLfoMillis;
elapsedMicros ellapsedLfoMicros;

uint32_t screenStepTime = 6; // ~15fps
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
  initializeKnobs();
  initializeButtons();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, ledState);

  setupLfos();

  menu.init(); 
  setupKnobMenu(knobs);
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

  long newControlKnobValue = controlKnob.read();
  if ((newControlKnobValue != controlKnobValue) && (abs(newControlKnobValue - controlKnobValue) > 4)) {
  // if (newControlKnobValue != controlKnobValue) {
    if (curMode != "PERFORMANCE") {
        if (newControlKnobValue > controlKnobValue) {
          menu.registerKeyPress(GEM_KEY_DOWN);
          screenDirty = true;
        } else {
          menu.registerKeyPress(GEM_KEY_UP);
          screenDirty = true;
        }
        controlKnobValue = newControlKnobValue;
      }
  }

  // for (int i = 0; i < 16; i++) {
  //   long newKnobValue = encoders[i]->read();
  //   if (newKnobValue != knobs[i]->encoder_value) {
  //     knobsDirty = true;
  //     ellapsedKnobTouchMillis = 0;
  //     screenSaver = false;
  //     knobs[i]->encoder_value = newKnobValue;
  //     usbMIDI.sendControlChange(knobs[i]->cc, newKnobValue, MIDI_CHANNEL);
  //     ledState = HIGH;
  //     digitalWrite(LED, ledState);
  //     ledMetro.interval(250);
  //     String knobtext = "knob " + String(i + 1) + ": " + String(newKnobValue);
  //     // drawText(knobtext, 1);
  //     Serial.println(knobtext);
  //     // drawText(knobtext, 9 * (i + 2));
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
    processLfos();
    ellapsedLfoMicros = ellapsedLfoMicros - lfoStepTime;
  }

// then do a calc cycle coupled with a midi send cycle...
// two loops
// first loop goes through all the knobs in order and gets output value / destination and accumulates it in variable for each knob
// second loop goes through accumulatied values
  // if accums.knob1 != accums_previous.knob1
  //   do calculcation on accums.knob1
  // gotta scale the value if other knobs are touching the knob.value.... 
  // i..e if knob2.lfo out goes to knob1.value, the new max value is 2....
  // is that right?
  //   send midi / change CV
// accums_previous = accums;
// probably sets accumulation back to zero? 



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
  // if (!screenSaver && (ellapsedKnobTouchMillis > SCREEN_SAVER_TIMEOUT_MS)) {
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
    String knobtext = "knob " + String(i + 1) + ": " + String(knobs[i]->encoder_value);
    drawText(knobtext, 1);
    String controlKnobText = "control knob :" + String(controlKnobValue);
    drawText(controlKnobText, 3);

  } else if (curMode == "KNOB") {
    // knobMenu.drawMenu();
    // screenDirty = true;
  } else if (curMode == "TEMPO") {
    // tempoMenu.drawMenu();
    // screenDirty = true;
  }

  if (Serial.available()) {
    char ch = Serial.read();
    Serial.print(ch);
    if(ch){ ellapsedKnobTouchMillis = 0;}
    if(ch == 'w'){ menu.registerKeyPress(GEM_KEY_UP);}
    if(ch == 'a'){ menu.registerKeyPress(GEM_KEY_LEFT);}
    if(ch == 'd'){ menu.registerKeyPress(GEM_KEY_RIGHT);}
    if(ch == 's'){ menu.registerKeyPress(GEM_KEY_DOWN);}
    if(ch == 'z'){ menu.registerKeyPress(GEM_KEY_CANCEL);}
    if(ch == 'c'){ menu.registerKeyPress(GEM_KEY_OK);}
  }
}
