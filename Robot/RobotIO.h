#pragma once
#include <stdint.h>

struct RobotIn {
	float gyroAngle;
  uint8_t sonicDistanceF;
  uint8_t sonicDistanceL;
  uint8_t sonicDistanceR;
  uint8_t sonicDistanceB;

  uint8_t shoulder;
  uint8_t wrist;

	RobotIn() :
		gyroAngle(0.0f),
    sonicDistanceF(0),
    sonicDistanceL(0),
    sonicDistanceR(0),
    sonicDistanceB(0),
    shoulder(0),
    wrist(0)
	{}
};

struct RobotOut {
	uint8_t driveFL;
	uint8_t driveBL;
	uint8_t driveFR;
	uint8_t driveBR;
	bool omni;

  uint8_t shoulder;
  uint8_t wrist;
  bool keyGrabber;

  uint8_t intake;
  uint8_t score;
  bool door;

	RobotOut() :
		driveFL(90),
		driveBL(90),
		driveFR(90),
		driveBR(90),
		omni(false),
    shoulder(90),
    wrist(90),
    keyGrabber(false),
    intake(90),
    score(90),
    door(false)
	{}
};

