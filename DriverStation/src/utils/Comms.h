#pragma once

#define BAUD_RATE	57600
#define TIMEOUT		500

#include "../robot/RobotIO.h"
#include "CRC8.h"
#include <serial/serial.h>
#include <iostream>
#include <windows.h>
using namespace serial;

class Comms {
public:
    // Public functions should not call each other. Otherwise deadlock
	Comms();

    bool read();
    bool write();

    void begin();
    void end();

    const RobotIn& getRobotIn();
    RobotOut& getRobotOut();
    void setRobotOut(const RobotOut &newStruct);

	bool maintainConnection();
    bool isEnded();
private:
    // private functions should not take lock
	Serial* serial;
    RobotOut out;
    RobotIn in;
    CRC8 crc8;

	unsigned char outBuf[8];
	void setOutBuf();

	void enumerate_ports();
};
