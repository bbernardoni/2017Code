#include "Key.h"

Key::Key() :
shoulderPid(PID::distance, SHOULDER_KP, SHOULDER_KI, SHOULDER_KD),
wristPid(PID::distance, WRIST_KP, WRIST_KI, WRIST_KD)
{
	lastGrabKey = false;
	state = manual;
	shoulderPid.setOutputLimits(0, 180);
	wristPid.setOutputLimits(0, 180);
}

void Key::periodic(const RobotIn& rIn, RobotOut& rOut){
	if(CTRL_RETRIEVE_POS){
		state = retrieve;
		shoulderPid.setTarget(SHOULDER_RET_POS);
		shoulderPid.reset();
		wristPid.setTarget(WRIST_RET_POS);
		wristPid.reset();
	}
	if(CTRL_INS_POS){
		state = insert;
		shoulderPid.setTarget(SHOULDER_INS_POS);
		shoulderPid.reset();
		wristPid.setTarget(WRIST_INS_POS);
		wristPid.reset();
	}
	if(CTRL_MAN_SHOULDER != 0.0f){
		state = manual;
	}
	if(CTRL_MAN_WRIST != 0.0f){
		state = manual;
	}

	bool inPos = true;
	switch(state){
	case manual:
		rOut.shoulder = uint8_t((CTRL_MAN_SHOULDER*MAN_SHOULDER_SPEED + 1) * 90);
		rOut.wrist = uint8_t((CTRL_MAN_WRIST*MAN_WRIST_SPEED + 1) * 90);
		break;
	case retrieve:
	case insert:
		rOut.shoulder = (uint8_t)shoulderPid.compute(rIn.shoulder);
		rOut.wrist = (uint8_t)wristPid.compute(rIn.wrist);
		break;
	}

	// grab key
	bool isPressed = CTRL_GRAB_KEY;
	if(isPressed && !lastGrabKey){
		rOut.keyGrabber = !rOut.keyGrabber;
	}
	lastGrabKey = isPressed;
}
