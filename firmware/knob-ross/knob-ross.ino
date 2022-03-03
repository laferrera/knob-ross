#include <Metro.h>
#include "display.h"
#include "controls.h"
// #include "menu.h"


#define LED 13
int ledState = HIGH;
Metro ledMetro = Metro(250);

#define MIDI_CHANNEL 1

// unsigned long lastTimeDisplayMillis = millis();
// unsigned long lastKnobTouchMillis = millis();
elapsedMillis ellapsedDisplayMillis;
elapsedMillis ellapsedKnobTouchMillis;
elapsedMillis ellapsedMetroMillis;
elapsedMillis ellapsedLfoMillis;

uint32_t screenStepTime = 6; // ~15fps
uint32_t lfoStepTime = 7;    //
uint32_t metroStepTime = 11; //

void setup() {
  Serial.begin(38400);
  // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read()) {
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.setFont(&font04B_034pt7b);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 9);
  display.println("knob ross");
  display.setCursor(0, 18);
  display.println("     knob ross");
  display.setCursor(0, 27);
  display.println("knob ross");
  display.setCursor(0, 36);
  display.println("     knob ross");
  display.println("knob ross");
  display.setCursor(0, 45);
  display.display();

  delay(2000); // Pause for 2 seconds
  //  display.clearDisplay();
  //  display.display();

  // Clear the buffer
  display.clearDisplay();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, ledState);
  buttonCancel.attach( buttonCancelPin,  INPUT_PULLUP ); // USE INTERNAL PULL-UP
  buttonOkay.attach( buttonOkayPin, INPUT_PULLUP );
  buttonCancel.interval(5); 
  buttonOkay.interval(5);   
  buttonCancel.setPressedState(LOW); 
  buttonOkay.setPressedState(LOW); 

  // initiaize knobs, should probably do this for banks.
  for (int i = 0; i < 16; i++) {
    Knob knob;
    knob.prev_val = -999;
    knob.cc = 102 + i;
    knob.phase = 0;
    knob.lfoType = 0;
    knob.minValue = 0;
    knob.maxValue = 127;
    knob.offset = 0;
    *knobs[i] = knob;
  }
}

void loop() {
// always check buttons and encoders  

  buttonCancel.update();
  buttonOkay.update();
  if (buttonCancel.fallingEdge()) {
    // button A pressed
  }
  if (buttonOkay.fallingEdge()) {
    // button pressed
  }
  

  for (int i = 0; i < 16; i++) {
    // Encoder encoder = *encoders[i];
    // long newKnobValue = encoder.read();
    long newKnobValue = encoders[i]->read();
    if (newKnobValue != knobs[i]->prev_val) {
      knobsDirty = true;
      ellapsedKnobTouchMillis = 0;
      screenSaver = false;
      knobs[i]->prev_val = newKnobValue;
      usbMIDI.sendControlChange(knobs[i]->cc, newKnobValue, MIDI_CHANNEL);
      ledState = HIGH;
      digitalWrite(LED, ledState);
      ledMetro.interval(250);
      String knobtext = "knob " + String(i + 1) + ": " + String(newKnobValue);
      drawText(knobtext, 1);
      Serial.println(knobtext);
      // drawText(knobtext, 9 * (i + 2));
    }
  }

  if (ledMetro.check() == 1) {
    ledState = LOW;
    digitalWrite(LED, ledState);
  }

  // screen cycle
  if (screenDirty && !screenSaver && (ellapsedDisplayMillis > screenStepTime)) {
    // update display
    // Serial.println("updating display");
    ellapsedDisplayMillis = ellapsedDisplayMillis - screenStepTime;
  }

  // lfo cycle
  if (ellapsedLfoMillis > lfoStepTime) {
    // update display
    // Serial.println("computing lfos");
    ellapsedLfoMillis = ellapsedLfoMillis - lfoStepTime;
  }

  // metro cycle
  if (ellapsedMetroMillis > metroStepTime) {
    // update metro
    // Serial.println("metro stuff");
    ellapsedMetroMillis = ellapsedMetroMillis - metroStepTime;
  }

  // check for incoming midi messages

  
  // Menu draw
  // menu.drawMenu();

  // screensaver cycle
  if (!screenSaver && (ellapsedKnobTouchMillis > SCREEN_SAVER_TIMEOUT_MS)) {
    // update display
    screenSaver = true;
    display.fillScreen(SSD1306_BLACK);
    display.display();
    Serial.println("screensaver on ");
  }

}
