#pragma once

struct RobotIn{
	float gyroAngle;
};

struct RobotOut{
	char driveFL;
	char driveBL;
	char driveFR;
	char driveBR;
	bool omni;
};

