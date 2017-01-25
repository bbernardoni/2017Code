#include "RobotIO.h"
#include <Servo.h>
#include <SPI.h>

// Robot input and output structs
RobotIn in;
RobotOut out;

// Drivetrain IO
int gyroPin;
Servo driveFL;
Servo driveBL;
Servo driveFR;
Servo driveBR;
int jumpPin;
  
/*
 * TODO
 * timeout code: stop motors if communication is lost
 */

void setup() {
  // init Drivetrain IO
  gyroPin = 6;
  driveFL.attach(1);
  driveBL.attach(2);
  driveFR.attach(3);
  driveBR.attach(4);
  jumpPin = 5;
  pinMode(jumpPin, OUTPUT);
  digitalWrite(jumpPin, LOW);
  /* TODO gyro stuff, ignore for now
  SPI.begin();
  pinMode(gyroPin, OUTPUT);
  digitalWrite(gyroPin, HIGH);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16); 
  SPI.setDataMode(SPI_MODE0);
  lastGyroRead = 0;
  gyroOffset = 0.0;*/

}

void loop() {
  // Get Robot input values and assign then to RobotIn
  in.gyroAngle = 0.0; // TODO assign real value

  // Send inputs to PC through serial
  // TODO

  // Read outputs from PC through serial
  // TODO

  // Write RobotOut values to outputs
  driveFL.write(out.driveFL);
  driveBL.write(out.driveBL);
  driveFR.write(out.driveFR);
  driveBR.write(out.driveBR);
  digitalWrite(jumpPin, out.omni);
}
