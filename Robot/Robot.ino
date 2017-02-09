#include "Config.h"

#include "RobotIO.h"
#include "Comm.h"

#include <Servo.h>
#include <SPI.h>
#include "Gyro.h"

// Robot input and output structs
RobotIn in;
RobotOut out;
Comm comm(&in, &out);

// Drivetrain IO
Gyro gyro(GYRO_PIN);
Servo driveFL;
Servo driveBL;
Servo driveFR;
Servo driveBR;
int jumpPin = JUMP_PIN;

/*
 * TODO
 * timeout code: stop motors if communication is lost
 */

void setup() {
  // init Drivetrain IO (gyro below)
  gyro.setup();
  driveFL.attach(DRIVE_FL_PIN);
  driveBL.attach(DRIVE_BL_PIN);
  driveFR.attach(DRIVE_FR_PIN);
  driveBR.attach(DRIVE_BR_PIN);
  pinMode(jumpPin, OUTPUT);
  digitalWrite(jumpPin, LOW);

  comm.begin(BAUD_RATE);
}

void loop() {
  // Get Robot input values and assign then to RobotIn
  in.gyroAngle = gyro.getAngle();

  // Write inputs to PC
  comm.write();
  delay(16);

  // Read output values to IO struct
  if(comm.read()){
    // Write RobotOut values to outputs
    driveFL.write(out.driveFL);
    driveBL.write(out.driveBL);
    driveFR.write(out.driveFR);
    driveBR.write(out.driveBR);
    digitalWrite(jumpPin, out.omni);
  }
}

