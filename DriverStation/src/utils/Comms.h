#pragma once

#define BAUD_RATE	115200
#define TIMEOUT		500

#include "../robot/RobotIO.h"
#include <serial/serial.h>
#include <iostream>
using namespace serial;

class Comms {
public:
	Comms();

	bool read();
	bool write();

	bool maintainConnection();

	RobotIn in;
	RobotOut out;

private:
	Serial* serial;

	void enumerate_ports();
};
