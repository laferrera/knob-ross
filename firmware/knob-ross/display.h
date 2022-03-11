#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include<SPI.h>
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "font04B_03.h"
#include "font04B_03_4pt.h"
#include "images.h"

// #define SCREEN_SAVER_TIMEOUT_MS 100000
#define SCREEN_SAVER_TIMEOUT_MS 10000
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C /// use Examples/Wire/Scanner to find the i2c address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

void startupScreen(){
  display.setFont(&font04B_034pt7b);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.drawBitmap(0, 0, ampamp_logo, 128, 64, 1);
  display.display();
  delay(1000);
  display.clearDisplay();
  for(int i = 0; i < 3; i++){
    display.println("lo and behold   lo and behold");
    display.display();
    delay(100);
    display.println("        lo and behold");
    display.display();
    delay(100);
  }
  display.setTextWrap(true);
  display.clearDisplay();
}

#endif