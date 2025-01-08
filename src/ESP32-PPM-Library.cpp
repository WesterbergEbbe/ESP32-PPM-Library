#include "ESP32PPM.h"

#define SYNC_THRESHOLD 3000 // Sync pulse length in microseconds (3 ms)

// Static member variables
volatile uint16_t *ESP32PPM::channelValues = nullptr;
volatile uint8_t ESP32PPM::currentChannel = 0;
volatile unsigned long ESP32PPM::lastPulseTime = 0;
uint8_t ESP32PPM::ppmPin = 0;
uint8_t ESP32PPM::numChannels = 0;

ESP32PPM::ESP32PPM(uint8_t pin, uint8_t numChannels) {
  ppmPin = pin;
  ESP32PPM::numChannels = numChannels;
  channelValues = new uint16_t[numChannels];
  for (uint8_t i = 0; i < numChannels; i++) {
    channelValues[i] = 0;
  }
}

void ESP32PPM::begin() {
  pinMode(ppmPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ppmPin), handlePPMInterrupt, RISING);
}

uint16_t ESP32PPM::getChannelValue(uint8_t channel) {
  if (channel >= numChannels) return 0; // Return 0 if channel index is out of bounds
  return channelValues[channel];
}

void IRAM_ATTR ESP32PPM::handlePPMInterrupt() {
  unsigned long currentTime = micros();                     // Get the current time
  unsigned long pulseLength = currentTime - lastPulseTime;  // Calculate pulse length
  lastPulseTime = currentTime;                              // Update last pulse time

  if (pulseLength > SYNC_THRESHOLD) {
    currentChannel = 0; // Sync pulse detected, reset channel index
  } else {
    if (currentChannel < numChannels) {
      channelValues[currentChannel] = pulseLength; // Store the pulse length
      currentChannel++;
    }
  }
}
