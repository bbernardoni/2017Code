#include "Drive.h"

Drive::Drive(DriveMode _mode){
	mode = _mode;
}

void Drive::periodic(const RobotIn& rIn, RobotOut& rOut){
	bool isPressed = CTRL_TOGGLE_MODE;
	if (isPressed && !modeBut){
		mode = (DriveMode)((mode + 1) % numModes);
		std::cout << "Mode changed to " << mode << std::endl;
	}
	modeBut = isPressed;
	switch (mode){
	case fieldCentric: {
		if (CTRL_GYRO_RESET){
			gyroOffset = rIn.gyroAngle;
		}
		isPressed = CTRL_GYRO_ROT_CCW;
		if (isPressed && !gyroCCWBut){
			gyroOffset += PI / 2.0f;
		}
		gyroCCWBut = isPressed;
		isPressed = CTRL_GYRO_ROT_CW;
		if (isPressed && !gyroCWBut){
			gyroOffset -= PI / 2.0f;
		}
		gyroCWBut = isPressed;

		float gyroAngle = PMod(rIn.gyroAngle - gyroOffset, PI*2.0f);
		fieldCentricControl(rOut, CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT, gyroAngle);
		rOut.omni = true;
		break; }
	case robotCentric:
		robotCentricControl(rOut, CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT);
		rOut.omni = true;
		break;
	case tank:
		rOut.driveBL = SOut(CTRL_TANK_LEFT);
		rOut.driveFL = SOut(CTRL_TANK_LEFT);
		rOut.driveBR = Rev(SOut(CTRL_TANK_RIGHT));
		rOut.driveFR = Rev(SOut(CTRL_TANK_RIGHT));
		rOut.omni = false;
		break;
	case autonomous:
		autonomousControl(rIn, rOut);
	}
}

void Drive::fieldCentricControl(RobotOut& rOut, float transX, float transY, float rot, float gyro){
	float robX = 0.0f;
	float robY = 0.0f;

	if (transX != 0.0f && transY != 0.0f){
		float transAngle = PMod(atan2(transY, transX) - gyro, PI*2.0f);
		float transMag = (fabs(transX) > fabs(transY)) ? fabs(transX) : fabs(transY);

		if (transAngle < PI / 4.0f || transAngle > 7.0f*PI / 4.0f){ // positive X is max
			robX = transMag;
			robY = robX*tan(transAngle);
		}
		else if (transAngle < 3.0f*PI / 4.0f){ // positive Y is max
			robY = transMag;
			robX = robY / tan(transAngle);
		}
		else if (transAngle < 5.0f*PI / 4.0f){ // negative X is max
			robX = -transMag;
			robY = robX*tan(transAngle);
		}
		else{ // negative Y is max
			robY = -transMag;
			robX = robY / tan(transAngle);
		}
	}

	robotCentricControl(rOut, robX, robY, rot);
}

void Drive::robotCentricControl(RobotOut& rOut, float transX, float transY, float rot){
	float backLeft = transY + transX + rot;
	float backRight = transY - transX - rot;
	float frontLeft = transY - transX + rot;
	float frontRight = transY + transX - rot;

	rOut.driveBL = SOut(Trunc(backLeft));
	rOut.driveBR = Rev(SOut(Trunc(backRight)));
	rOut.driveFL = SOut(Trunc(frontLeft));
	rOut.driveFR = Rev(SOut(Trunc(frontRight)));
}


void Drive::autonomousControl(const RobotIn& rIn, RobotOut& rOut){
	switch (directionState){
	case front:
		/*move in direction1*/
		getSonarValue(rIn);
		if (isBlocked(sonarF)) directionState = getNextDirection();
		robotCentricControl(rOut, 0, CONSTANT_SHIFT, 0);
		break;
	case right:
		/*move in direction2*/
		getSonarValue(rIn);
		if (isBlocked(sonarR)) directionState = getNextDirection();
		robotCentricControl(rOut, CONSTANT_SHIFT, 0, 0);
		break;
	case back:
		/*move in direction3*/
		getSonarValue(rIn);
		if (isBlocked(sonarB)) directionState = getNextDirection();
		robotCentricControl(rOut, 0, -CONSTANT_SHIFT, 0);
		break;
	case left:
		/*move in direction4*/
		getSonarValue(rIn);
		if (isBlocked(sonarL)) directionState = getNextDirection();
		robotCentricControl(rOut, -CONSTANT_SHIFT, 0, 0);
		break;
	}
}

Drive::direction Drive::getNextDirection(){
	if (directionState == front || directionState == back){
		if (isBlocked(right)) return left;
		else return right;
	}
	else {
		if (isBlocked(front)) return back;
		else return front;
	}
}

Drive::direction Drive::getCurrentDirection(){
	return directionState;
}

bool Drive::isBlocked(int dis){
	if (dis < BLOCK_DISTANCE) return true;	//need to define max distance
	return false;
}

void Drive::getSonarValue(const RobotIn& rIn){
	sonarF = rIn.sonicDistanceF;
	sonarR = rIn.sonicDistanceR;
	sonarB = rIn.sonicDistanceB;
	sonarL = rIn.sonicDistanceL;
	//read sonar value from robot
}