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

	switch(state){
	case manual:
		rOut.shoulder = CTRL_MAN_SHOULDER;
		rOut.wrist = CTRL_MAN_WRIST;
		break;
	case retrieve:
		bool inPos = true;
		// execute pid

		if(inPos){
			state = manual;
		}
		break;
	case insert:
		bool inPos = true;

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
