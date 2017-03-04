#include "Key.h"

Key::Key(){
	lastGrabKey = false;
	state = manual;
}

void Key::periodic(const RobotIn& rIn, RobotOut& rOut){
	if(CTRL_RETRIEVE_POS){
		state = retrieve;
	}
	if(CTRL_INS_POS){
		state = insert;
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
		rOut.shoulder = uint8_t((CTRL_MAN_SHOULDER + 1) * 90);
		rOut.wrist = uint8_t((CTRL_MAN_WRIST + 1) * 90);
		break;
	case retrieve:
		// execute pid

		if(inPos){
			state = manual;
		}
		break;
	case insert:

		if(inPos){
			state = manual;
		}
		break;
	}

	// grab key
	bool isPressed = CTRL_GRAB_KEY;
	if(isPressed && !lastGrabKey){
		rOut.keyGrabber = !rOut.keyGrabber;
	}
	lastGrabKey = isPressed;
}
