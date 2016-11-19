#pragma once

#include "Drive.h"
#include "RobotIO.h"

class Robot {
public:
	Robot(Drive::DriveMode _mode);
	void periodic(const RobotIn& rIn, RobotOut& rOut);

private:
	Drive drive;
};
