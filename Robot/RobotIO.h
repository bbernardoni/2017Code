#pragma once
#include <stdint.h>

struct RobotIn{
	float gyroAngle;

	RobotIn() :
		gyroAngle(0.0f)
	{}
};

struct RobotOut{
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

