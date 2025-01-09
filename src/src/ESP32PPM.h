#ifndef ESP32PPM_H
#define ESP32PPM_H

#include <Arduino.h>

class ESP32PPM {
public:
  ESP32PPM(uint8_t pin, uint8_t numChannels);
  void begin();
  uint16_t getChannelValue(uint8_t channel);

private:
  static void IRAM_ATTR handlePPMInterrupt();
  static volatile uint16_t *channelValues; // Store channel pulse widths
  static volatile uint8_t currentChannel;
  static volatile unsigned long lastPulseTime;
  static uint8_t ppmPin;
  static uint8_t numChannels;
};

#endif
