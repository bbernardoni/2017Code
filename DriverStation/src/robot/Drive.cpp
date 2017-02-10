#include "Drive.h"

Drive::Drive(DriveMode _mode){
	mode = _mode;
}

void Drive::periodic(const RobotIn& rIn, RobotOut& rOut){
	bool isPressed = CTRL_TOGGLE_MODE;
	if(isPressed && !modeBut){
		mode = (DriveMode)((mode + 1) % numModes);
		std::cout << "Mode changed to " << mode << std::endl;
	}
	modeBut = isPressed;
	switch(mode){
	case fieldCentric: {
		if(CTRL_GYRO_RESET){
			gyroOffset = rIn.gyroAngle;
		}
		isPressed = CTRL_GYRO_ROT_CCW;
		if(isPressed && !gyroCCWBut){
			gyroOffset += PI / 2.0f;
		}
		gyroCCWBut = isPressed;
		isPressed = CTRL_GYRO_ROT_CW;
		if(isPressed && !gyroCWBut){
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
		rOut.driveBR = SOut(CTRL_TANK_RIGHT);
		rOut.driveFR = SOut(CTRL_TANK_RIGHT);
		rOut.omni = false;
		break;
	}
}

void Drive::fieldCentricControl(RobotOut& rOut, float transX, float transY, float rot, float gyro){
	float robX = 0.0f;
	float robY = 0.0f;

	if(transX != 0.0f && transY != 0.0f){
		float transAngle = PMod(atan2(transY, transX) - gyro, PI*2.0f);
		float transMag = (fabs(transX) > fabs(transY))? fabs(transX): fabs(transY);
    
		if(transAngle < PI/4.0f || transAngle > 7.0f*PI/4.0f){ // positive X is max
			robX = transMag;
			robY = robX*tan(transAngle);
		}else if(transAngle < 3.0f*PI/4.0f){ // positive Y is max
			robY = transMag;
			robX = robY/tan(transAngle);
		}else if(transAngle < 5.0f*PI/4.0f){ // negative X is max
			robX = -transMag;
			robY = robX*tan(transAngle);
		}else{ // negative Y is max
			robY = -transMag;
			robX = robY/tan(transAngle);
		}
	}
  
	robotCentricControl(rOut, robX, robY, rot);
}

void Drive::robotCentricControl(RobotOut& rOut, float transX, float transY, float rot){
	float backLeft = transY - transX + rot;
	float backRight = transY + transX + rot;
	float frontLeft = -transY + transX + rot;
	float frontRight = -transY - transX + rot;

	rOut.driveBL = SOut(Trunc(backLeft));
	rOut.driveBR = SOut(Trunc(backRight));
	rOut.driveFL = SOut(Trunc(frontLeft));
	rOut.driveFR = SOut(Trunc(frontRight));
}
