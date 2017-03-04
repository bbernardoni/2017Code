#include "Ball.h"

Ball::Ball() {
	scoring = false;
	scoreStartTime = 0;
	intakeState = false;
	solenoidState = false;
}

void Ball::periodic(const RobotIn& rIn, RobotOut& rOut) {

	// If ball intake button is pressed (create in Controls.h), toggle intake motor
	if (CTRL_INTAKE && !intakeState) {
		intakeState = true;
	}
	else if (CTRL_INTAKE && intakeState) {
		intakeState = false;
	}

	if (intakeState) {
		rOut.intake = INTAKE_ON;
	}
	else {
		rOut.intake = INTAKE_OFF;
	}

	// If raise door button is pressed, toggle solenoid
	if (CTRL_DOOR && !solenoidState) {
		solenoidState = true;
	}
	else if (CTRL_DOOR && solenoidState) {
		solenoidState = false;
	}

	if (solenoidState) {
		rOut.solenoid = SOLENOID_ON;
	}
	else {
		rOut.solenoid = SOLENOID_OFF;
	}

	// If score button, toggle score motor for some period of time
	if (CTRL_SCORE) {
		scoring = true;
		scoreStartTime = time(0); // Get current time
		rOut.score = SCORE_POSN;
	}

	if (scoring && (time(0) - scoreStartTime > HOLD_TIME)) {
		scoring = false;
		rOut.score = HOLD_POSN;
	}


}
