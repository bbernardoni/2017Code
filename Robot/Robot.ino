#include "RobotIO.h"
#include "Comm.h"
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

Comm comm(50, 9600, &in, &out);

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

  comm.begin();
}

void loop() {
  // Get Robot input values and assign then to RobotIn

  // Send inputs to PC through serial
  // TODO

  // Read outputs from PC through serial
  // TODO

  // Write RobotOut values to outputs
//  driveFL.write(out.driveFL);
//  driveBL.write(out.driveBL);
//  driveFR.write(out.driveFR);
//  driveBR.write(out.driveBR);
//  digitalWrite(jumpPin, out.omni);
//  delay();
  unsigned char temp[4];
  temp[0] = out.driveFL;
  temp[1] = out.driveBL;
  temp[2] = out.driveFR;
  temp[3] = out.driveBR;
  float * tmp = (float *) temp;
  in.gyroAngle = *tmp;
}
