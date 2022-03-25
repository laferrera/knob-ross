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
int graphValue;
String graphChannelLabel;
String graphChannelHUDFreq;
String graphChannelHUDAmp;
String graphChannelHUDWaveform;

void initializeGraphs() {
  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      graphQueues[i].push(0);
    }
  }
}

void drawGraph(int channelIndex, bool hud, float hz) {
  display.clearDisplay();
  String graphChannelLabel = "Channel " + String(channelIndex + 1);
  display.setCursor(0, (SCREEN_HEIGHT - 8));
  display.println(graphChannelLabel);
  if(hud) {
    display.setCursor(0, (SCREEN_HEIGHT - 16));
    graphChannelHUDFreq = String(hz) + " Hz";
    display.print(graphChannelHUDFreq);
  } 


  for (int i = 0; i < SCREEN_WIDTH; i++) {
    // TODO find the real problem here....
    // graphValue = graphQueues[channelIndex][i] != NULL ? 0 : graphQueues[channelIndex][i];
    // graphValue = static_cast<int>(graphValue * 32 + 32);
    
    // graphValue = static_cast<int>(graphQueues[channelIndex][i] * (-32) + 32);
    // Result := ((Input - InputLow) / (InputHigh - InputLow)) * (OutputHigh - OutputLow) + OutputLow;
    graphValue = int(((graphQueues[channelIndex][i] + 1) / 2) * -63 + 63);

    display.drawPixel(i, graphValue, WHITE);
  }

  screenDirty = true;
}

#endif
