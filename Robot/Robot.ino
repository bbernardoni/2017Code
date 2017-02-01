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

// Gyro globals
unsigned long lastGyroRead;
int gyroSpeed;
float gyroAngle;
float gyroOffset;

/*
 * TODO
 * timeout code: stop motors if communication is lost
 */

// Positive Modulus helper function (n%i)
static float PMod(float n, float i) { return n-i*floor(n/i); }

float getGyroAngle(){
  unsigned long readTime = micros();
  if(lastGyroRead == 0)
    lastGyroRead = readTime;
  
  digitalWrite(gyroPin, LOW);
  int result = SPI.transfer(0x20);
  result = result << 8 | SPI.transfer(0x00);
  int result2 = SPI.transfer(0x00) >>2;
  SPI.transfer(0x00);
  result = result << 6 | result2;
  digitalWrite(gyroPin, HIGH);

  // low pass filter
  gyroSpeed = (gyroSpeed)*0.5 + result*(1 - 0.5);
  // gyro returns in units of 80 LSB/deg/sec

  if(abs(gyroSpeed) > 40){
    gyroAngle += gyroSpeed/80.0*(readTime-lastGyroRead)/1000000.0;
    //Serial.println(gyroSpeed);
  }
  lastGyroRead = readTime;
  
  return PMod(gyroAngle - gyroOffset, PI*2.0);
}

void setup() {
  // init Drivetrain IO (gyro below)
  driveFL.attach(1);
  driveBL.attach(2);
  driveFR.attach(3);
  driveBR.attach(4);
  jumpPin = 5;
  pinMode(jumpPin, OUTPUT);
  digitalWrite(jumpPin, LOW);

  // init Gyro
  gyroPin = 6;
  pinMode(gyroPin, OUTPUT);
  digitalWrite(gyroPin, HIGH);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16); 
  SPI.setDataMode(SPI_MODE0);
  lastGyroRead = 0;
  gyroSpeed = 0;
  gyroAngle = 0.0;
  gyroOffset = 0.0;
}

void loop() {
  // Get Robot input values and assign then to RobotIn
  in.gyroAngle = getGyroAngle();

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
