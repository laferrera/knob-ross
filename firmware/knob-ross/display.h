#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include<SPI.h>
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "font04B_03.h"
#include "font04B_03_4pt.h"

// #define SCREEN_SAVER_TIMEOUT_MS 100000
#define SCREEN_SAVER_TIMEOUT_MS 10000
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

bool screenDirty = false;
bool screenSaver = false;

void drawText(String text, uint8_t line) {
  display.clearDisplay();
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 10 * line);     // Start at top-left corner
  display.println(text);
  screenDirty = true;
  //   display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  //   display.setTextSize(2);             // Draw 2X-scale text
}

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
      (display.width() - LOGO_WIDTH) / 2,
      (display.height() - LOGO_HEIGHT) / 2,
      logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);

  delay(1000);
}

void startupScreen(){
  display.setFont(&font04B_034pt7b);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 9);
  display.println("lo and behold   lo and behold");
  display.setCursor(0, 18);
  display.println("        lo and behold");
  display.setCursor(0, 27);
  display.println("lo and behold   lo and behold");
  display.setCursor(0, 36);
  display.println("        lo and behold");
  display.setCursor(0, 45);
  display.println("lo and behold   lo and behold");
  display.setCursor(0, 54);
  display.println("        lo and behold");
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}

#endif