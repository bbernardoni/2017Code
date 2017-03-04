#include "Config.h"

#include "RobotIO.h"
#include "Comm.h"

#include <Servo.h>
#include <SPI.h>
#include "Gyro.h"
#include <NewPing.h>

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
// declare sonic sensors here
// using SONIC_T_F_PIN, SONIC_E_F_PIN, ...
NewPing sonicFront(SONIC_T_F_PIN, SONIC_E_F_PIN) ;
NewPing sonicLeft(SONIC_T_L_PIN, SONIC_E_L_PIN);
NewPing sonicRight(SONIC_T_R_PIN, SONIC_E_R_PIN);
NewPing sonicBack(SONIC_T_B_PIN, SONIC_E_B_PIN);

// Key IO
Servo shoulderMotor;
Servo wristMotor;
int shoulderPotPin = SHOULDER_POT_PIN;
int wristPotPin = WRIST_POT_PIN;
int keyGrabberPin = KEY_GRABBER_PIN;

// Ball IO
Servo intake;
Servo scoreServo;
int doorPin = DOOR_PIN;

void setup() {
  // init Drivetrain IO
  gyro.setup();
  driveFL.attach(DRIVE_FL_PIN);
  driveBL.attach(DRIVE_BL_PIN);
  driveFR.attach(DRIVE_FR_PIN);
  driveBR.attach(DRIVE_BR_PIN);
  pinMode(jumpPin, OUTPUT);
  digitalWrite(jumpPin, LOW);
  // init sonic sensors here
  
  // init Key IO
  shoulderMotor.attach(SHOULDER_MOTOR_PIN);
  wristMotor.attach(WRIST_MOTOR_PIN);
  pinMode(keyGrabberPin, OUTPUT);
  digitalWrite(keyGrabberPin, LOW);

  // init Ball IO
  intake.attach(INTAKE_PIN);
  scoreServo.attach(SCORE_PIN);
  pinMode(doorPin, OUTPUT);
  digitalWrite(doorPin, LOW);
  
  comm.begin(BAUD_RATE);
}

void loop() {
  // Get Robot input values and assign then to RobotIn
  in.gyroAngle = gyro.getAngle();
  // set in.sonicDistanceF, ... here
  
  //write distances to in struct in inches
  in.sonicDistanceF = sonicFront.ping_in();
  in.sonicDistanceL = sonicLeft.ping_in();
  in.sonicDistanceR = sonicRight.ping_in();
  in.sonicDistanceB = sonicBack.ping_in();
  
  in.shoulder = analogRead(shoulderPotPin);
  in.wrist = analogRead(wristPotPin);

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

    shoulderMotor.write(out.shoulder);
    wristMotor.write(out.wrist);
    digitalWrite(keyGrabberPin, out.keyGrabber);
    
    intake.write(out.intake);
    scoreServo.write(out.score);
    digitalWrite(doorPin, out.door);
  }else if(comm.getFailures() > 30){
    driveFL.write(90);
    driveBL.write(90);
    driveFR.write(90);
    driveBR.write(90);
    shoulderMotor.write(90);
    wristMotor.write(90);
    intake.write(90);
  }
}

