#pragma once

#include "RobotIO.h"
#include "Controls.h"
#include "Constants.h"

#include <ctime>

class Ball {
public:
	Ball();
	void periodic(const RobotIn& rIn, RobotOut& rOut);

private:
	bool scoring;
	clock_t scoreStartTime;
	bool intakeState;
	bool lastGrabIntakeKey;
	bool lastGrabDoorOutKey;
	bool lastGrabDoorUpKey;
};
