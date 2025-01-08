#include <ESP32PPM.h>
#include <ESP32Servo.h>

#define PPM_PIN 5         // GPIO pin connected to the PPM signal
#define NUM_CHANNELS 6    // Number of channels in the PPM signal
#define Servo_Ammount 1 // Number of servos connected

ESP32PPM ppmReader(PPM_PIN, NUM_CHANNELS); // Initialize the library
Servo servos[Servo_Ammount]; // Array to handle multiple servos
int servoPins[Servo_Ammount] = {18}; // Define pins for the servos

int pos = 0;



void setup() {
  	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  for (int i = 0; i < Servo_Ammount; i++) {
    servos[i].setPeriodHertz(50);           // Standard 50 Hz servo
    servos[i].attach(servoPins[i], 1000, 2000); // Attach servo with min/max pulse width (1000-2000us)
  }
  ppmReader.begin(); // Start PPM reading
}

void loop() {
  // Read the pulse width of each PPM channel
  for (int i = 0; i < Servo_Ammount; i++) {
    uint16_t pulseWidth = ppmReader.getChannelValue(i);

    // Map pulse width to servo position (0-180 degrees)
    int servoPosition = map(pulseWidth, 1000, 2000, 0, 180);

    // Clamp the position to valid servo range
    servoPosition = constrain(servoPosition, 0, 180);
    servos[i].write(servoPosition);

  }

  delay(20);
}