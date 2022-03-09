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
  int operator[](int index) {
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
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        // float graphValue = graphQueues[channelIndex].front();
        // graphQueues[channelIndex].pop();
        // graphQueues[channelIndex].push(graphValue);
        // display.drawPixel(i, SCREEN_HEIGHT - graphValue, WHITE);

        int graphValue = static_cast<int>(graphQueues[channelIndex][i] * 64 + 128);
        display.drawPixel(i, SCREEN_HEIGHT - graphValue, WHITE);
        // float graphValue = graphQueues[channelIndex][i] * 64 + 128;
        
    }
    screenDirty = true;
}

#endif