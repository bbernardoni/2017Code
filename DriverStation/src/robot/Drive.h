#pragma once

#include "RobotIO.h"
#include "Controls.h"
#include <cmath>
#define PI 3.14159265358979323846f

class Drive {
public:
	enum DriveMode { fieldCentric, robotCentric };
    
	Drive(DriveMode _mode);
	void periodic(const RobotIn& rIn, RobotOut& rOut);
    
	// Positive Modulus (n%i)
	static float PMod(float n, float i) { return n - i*floor(n / i); }
	// converts from [-1.0, 1.0] to [0,180] for servo write
	static int SOut(float out) { return int((out+1.0f)*90.0f); }
	// reverses from [180,0] to [0,180] for servo write
	static int Rev(int out) { return 180-out; }

private:
	void fieldCentricControl(RobotOut& rOut, float transX, float transY, float rot, float gyro);
	void robotCentricControl(RobotOut& rOut, float transX, float transY, float rot);

	DriveMode mode;
	float gyroOffset;
};
