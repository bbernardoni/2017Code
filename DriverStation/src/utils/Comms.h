#pragma once

#include "../robot/RobotIO.h"
#include <serial/serial.h>
#include <iostream>
using namespace serial;

class Comms {
public:
	Comms();

	void read();
	void write();

	RobotIn in;
	RobotOut out;

private:
};
