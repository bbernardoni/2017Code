#include "Key.h"

Key::Key()
{
	lastGrabKey = false;
}

void Key::periodic(const RobotIn& rIn, RobotOut& rOut){
	double holdOffset = HOLD_SHOULDER_SPEED*sin((rIn.shoulder - SHOULDER_MID)*SHOULDER_RAD);
	double shoulder = CTRL_MAN_SHOULDER*MAN_SHOULDER_SPEED + holdOffset;
	//rOut.shoulder = 90; std::cout << "rIn.shoulder = " << rIn.shoulder << " rOut.shoulder = "  << shoulder << std::endl;
	rOut.shoulder = uint8_t((shoulder + 1) * 90);
	rOut.wrist = uint8_t((CTRL_MAN_WRIST*MAN_WRIST_SPEED + 1) * 90);

	// grab key
	bool isPressed = CTRL_GRAB_KEY;
	if(isPressed && !lastGrabKey){
		rOut.keyGrabber = !rOut.keyGrabber;
	}
	lastGrabKey = isPressed;
}
