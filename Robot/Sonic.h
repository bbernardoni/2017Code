#ifndef SONIC_H
#define SONIC_H

// Represents one ultrasonic sensor
class Sonic {

public:
  // Returns the distance to the nearest object the sensor can sense, in centimeters
  int sonarRead(const int sonicOutputPin, const int sonicInputPin);
  
};

#endif 

