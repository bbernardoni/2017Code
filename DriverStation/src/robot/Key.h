#pragma once

#include "RobotIO.h"
#include "Controls.h"
#include "../utils/PID.h"
#include "Constants.h"
#include <iostream>

class Key {
public:
	Key();
	void periodic(const RobotIn& rIn, RobotOut& rOut);

	enum KeyState { manual, retrieve, insert };

private:
	bool lastGrabKey;
	KeyState state;
	PID shoulderPid;
	PID wristPid;
};
