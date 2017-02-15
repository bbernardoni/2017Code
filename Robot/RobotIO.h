#pragma once
#include <stdint.h>

struct RobotIn {
	float gyroAngle;
  uint8_t sonicDistanceF;
  uint8_t sonicDistanceL;
  uint8_t sonicDistanceR;
  uint8_t sonicDistanceB;

	RobotIn() :
		gyroAngle(0.0f),
    sonicDistanceF(0),
    sonicDistanceL(0),
    sonicDistanceR(0),
    sonicDistanceB(0)
	{}
};

struct RobotOut {
	uint8_t driveFL;
	uint8_t driveBL;
	uint8_t driveFR;
	uint8_t driveBR;
	int8_t omni;

	RobotOut() :
		driveFL(90),
		driveBL(90),
		driveFR(90),
		driveBR(90),
		omni((int8_t)false)
	{}
};

