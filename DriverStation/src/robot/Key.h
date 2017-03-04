#pragma once

#include "RobotIO.h"
#include "Controls.h"

class Key {
public:
	Key();
	void periodic(const RobotIn& rIn, RobotOut& rOut);

	enum KeyState { manual, retrieve, insert };

private:
	bool lastGrabKey;
	KeyState state;
};
