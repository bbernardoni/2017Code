#include "Sonic.h"
#include <Arduino.h>

// Returns the distance to the nearest object the sensor can sense, in inches
// Inputs: 
//   sonicOutputPin - the pin associated with sending out a wave
//   sonincInputPin - the pin associated with receiving of a wave echo
int Sonic::sonarRead(const int sonicOutputPin, const int sonicInputPin) {

  long duration, inches;

  // Send out an ultrasonic wave
  digitalWrite(sonicOutputPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonicOutputPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonicOutputPin, LOW);

  // Duration (in microseconds) between sending of ultrasonic wave and receiving its echo
  duration = pulseIn(sonicInputPin, HIGH);

  // Convert duration to distance between sensor and object that the wave reflected off of
  inches = duration / 74 / 2;
  
  return inches;
}
