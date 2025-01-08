#include <ESP32PPM.h>

#define PPM_PIN 5         // GPIO pin connected to the PPM signal
#define NUM_CHANNELS 6    // Number of channels in the PPM signal

ESP32PPM ppmReader(PPM_PIN, NUM_CHANNELS); // Initialize the library

void setup() {
  Serial.begin(9600);
  ppmReader.begin(); // Start PPM reading
}

void loop() {
  // Read the pulse width of each PPM channel
  for (int i = 0; i < NUM_CHANNELS; i++) {
    uint16_t pulseWidth = ppmReader.getChannelValue(i);

    // Map pulse width to servo position (0-180 degrees)
    int servoPosition = map(pulseWidth, 1000, 2000, 0, 180);

    // Clamp the position to valid servo range
    servoPosition = constrain(servoPosition, 0, 180);

    // Print the servo position
    Serial.print("Channel ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(servoPosition);
  }

  delay(20);
}
