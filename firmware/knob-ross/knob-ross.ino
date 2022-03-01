#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "font04B_03.h"
#include <Encoder.h>
#include <Bounce.h>
#include <Metro.h>

#define LED 13
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C /// use Examples/Wire/Scanner to find the i2c address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char PROGMEM logo_bmp[] =
    {0b00000000, 0b11000000,
     0b00000001, 0b11000000,
     0b00000001, 0b11000000,
     0b00000011, 0b11100000,
     0b11110011, 0b11100000,
     0b11111110, 0b11111000,
     0b01111110, 0b11111111,
     0b00110011, 0b10011111,
     0b00011111, 0b11111100,
     0b00001101, 0b01110000,
     0b00011011, 0b10100000,
     0b00111111, 0b11100000,
     0b00111111, 0b11110000,
     0b01111100, 0b11110000,
     0b01110000, 0b01110000,
     0b00000000, 0b00110000};

// Map the TeensyLC pins to each potentiometer numbered left to right.
Encoder enc1(0, 1);
Encoder enc2(2, 3);
Encoder enc3(4, 5);
Encoder enc4(6, 7);
Encoder enc5(8, 9);
Encoder enc6(10, 11);
Encoder enc7(12, 24);
// skip 13, cause that's led
Encoder enc8(25, 26);
Encoder enc9(27, 28);
Encoder enc10(29, 30);
Encoder enc11(31, 32);
Encoder enc12(33, 34);
Encoder enc13(35, 36);
Encoder enc14(37, 38);
Encoder enc15(39, 40);
Encoder enc16(41, 14);
Encoder controlKnob(15, 16);

int buttonApin = 22;
int buttonBpin = 23;
Bounce buttonA = Bounce(22, 5);
Bounce buttonB = Bounce(23, 5);

#define MIDI_CHANNEL 1

// potentiometer read parameters
#define POT_BIT_RES 10 // 10 works, 7-16 is valid

struct Knob
{
  int prev_val;
  uint8_t cc;
  int phase;
  int minValue;
  uint8_t maxValue;
  int offset;
  uint8_t lfoType;
  uint8_t knobDestination;
  uint8_t lfoDestination;
};

struct Knob knob1;
struct Knob knob2;
struct Knob knob3;
struct Knob knob4;
struct Knob knob5;
struct Knob knob6;
struct Knob knob7;
struct Knob knob8;
struct Knob knob9;
struct Knob knob10;
struct Knob knob11;
struct Knob knob12;
struct Knob knob13;
struct Knob knob14;
struct Knob knob15;
struct Knob knob16;

uint16_t prev_enc_val[17] = {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};
Encoder *encoders[17] = {&enc1, &enc2, &enc3, &enc4, &enc5, &enc6, &enc7, &enc8, &enc9, &enc10, &enc11, &enc12, &enc13, &enc14, &enc15, &enc16};
// Knob *knobs[16] = {};
Knob *knobs[16] = {&knob1, &knob2, &knob3, &knob4, &knob5, &knob6, &knob7, &knob8, &knob9, &knob10, &knob11, &knob12, &knob13, &knob14, &knob15, &knob16};

int ledState = HIGH;
int buttonAState = HIGH;
int buttonBState = HIGH;
Metro ledMetro = Metro(250);
bool screenDirty = false;
uint32_t lastTimeDisplayMillis = millis();
uint32_t screenStepTime = 6; // ~15fps
uint32_t lfoStepTime = 6; // ~15fps
uint32_t metroStepTime = 12; // ~7fps

void drawText(String text, uint8_t line)
{
  display.clearDisplay();
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 9 * line);      // Start at top-left corner
  display.println(text);
  display.display();
  //   display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  //   display.setTextSize(2);             // Draw 2X-scale text
}

void testdrawbitmap(void)
{
  display.clearDisplay();

  display.drawBitmap(
      (display.width() - LOGO_WIDTH) / 2,
      (display.height() - LOGO_HEIGHT) / 2,
      logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

void redrawDisplay(void){
  if (screenDirty && (millis() - lastTimeDisplayMillis > 10)) {
    display.display();
    lastTimeDisplayMillis = millis();
  }
}

void setup()
{
  Serial.begin(38400);
  // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read())
  {
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.setFont(&font04B_038pt7b);
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
   pinMode(buttonApin, INPUT_PULLUP);
   pinMode(buttonBpin, INPUT_PULLUP);
  for (int i = 0; i < 16; i++)
  {
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


void loop(){
  
  buttonA.update();
  buttonB.update();

  for (int i = 0; i < 16; i++)
  {
    Encoder encoder = *encoders[i];

    long newKnobValue = encoder.read();
    if (newKnobValue != knobs[i]->prev_val)
    {
      knobs[i]->prev_val = newKnobValue;
      usbMIDI.sendControlChange(knobs[i]->cc, newKnobValue >> (POT_BIT_RES - 7), MIDI_CHANNEL);
      ledState = HIGH;
      digitalWrite(LED, ledState);
      ledMetro.interval(250);
      String knobtext = "knob " + String(i + 1) + ": " + String(newKnobValue);
      drawText(knobtext, 1);
      Serial.println(knobtext);
      // drawText(knobtext, 9 * (i + 2));
    }
   }
  
   if (ledMetro.check() == 1){
     ledState = LOW;
     digitalWrite(LED, ledState);
   }
   if (digitalRead(buttonApin) == LOW){
     buttonAState = LOW;
   }
   if (digitalRead(buttonBpin) == LOW){
     buttonBState = LOW;
   }

  if (Serial.available())
  {
    Serial.read();
    Serial.println("Reset knobs to zero");
    for (int i = 0; i < 16; i++)
    {
      Encoder encoder = *encoders[i];
      encoder.write(0);
    }
  }
}
