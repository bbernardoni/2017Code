#include "Ball.h"

Ball::Ball() {
	scoring = false;
	scoreStartTime = 0;
	intakeState = false;
	lastGrabIntakeKey = false;
	lastGrabDoorOutKey = false;
	lastGrabDoorUpKey = false;
}

void Ball::periodic(const RobotIn& rIn, RobotOut& rOut) {

	// If ball intake button is pressed (create in Controls.h), toggle intake motor
	if (CTRL_INTAKE && !lastGrabIntakeKey) {
		intakeState = !intakeState;
	}
	lastGrabIntakeKey = CTRL_INTAKE;

	if (intakeState) {
		rOut.intake = INTAKE_ON;
	}
	else {
		rOut.intake = INTAKE_OFF;
	}


	// If raise door button is pressed, toggle solenoid
	if(CTRL_DOOR_OUT && !lastGrabDoorOutKey) {
		rOut.doorOut = !rOut.doorOut;
	}
	lastGrabDoorOutKey = CTRL_DOOR_OUT;

	if(CTRL_DOOR_UP && !lastGrabDoorUpKey) {
		rOut.doorUp = !rOut.doorUp;
	}
	lastGrabDoorUpKey = CTRL_DOOR_UP;

	// If score button, toggle score motor for some period of time
	if (CTRL_SCORE) {
		scoring = true;
		scoreStartTime = clock(); // Get current time
		rOut.score = SCORE_POSN;
	}

	if (scoring && ((double)(clock() - scoreStartTime) / CLOCKS_PER_SEC > HOLD_TIME)) {
		scoring = false;
		rOut.score = HOLD_POSN;
	}


}
