#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <array>
#include <deque>
#include <queue>
#include <array>

template <typename T, int MaxLen, typename Container = std::deque<T>>
class FixedQueue : public std::queue<T, Container> {
public:
  void push(const T &value) {
    if (this->size() == MaxLen) {
      this->c.pop_front();
    }
    std::queue<T, Container>::push(value);
  }
  float operator[](int index) {
    return this->c[index];
  }
};

// template <typename T, int MaxLen, typename Container = std::deque<T>>
// class FixedQueue : public std::deque<T, Container> {
// public:
//   void push(const T &value) {
//     if (this->size() == MaxLen) {
//       this->pop_front();
//     }
//     std::deque<T, Container>::push_back(value);
//   }
// };

std::array<FixedQueue<float, SCREEN_WIDTH>, NUM_OF_CHANNELS> graphQueues;

void initializeGraphs(){
  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      graphQueues[i].push(0);
    }
  }
}

void drawGraph(int channelIndex){
    display.clearDisplay();
    String channeltext = "Channel " + String(channelIndex + 1);
    // display.setTextSize(1);              // Normal 1:1 pixel scale
    // display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, (SCREEN_HEIGHT - 10)); // Start at top-left corner
    display.println(channeltext);
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        int graphValue = static_cast<int>(graphQueues[channelIndex][i] * 32 + 32);
        // Serial.println("graph value i" + String(graphQueues[channelIndex][i]));
        // Serial.println("graph value cast" + String(graphValue));
        display.drawPixel(i, graphValue, WHITE);
    }
    screenDirty = true;
}

#endif