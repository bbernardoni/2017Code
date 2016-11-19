#include "Drive.h"

Drive::Drive(DriveMode _mode){
	mode = _mode;
}

void Drive::periodic(const RobotIn& rIn, RobotOut& rOut){
	switch(mode){
	case fieldCentric: {
		if(CTRL_GYRO_RESET){
			gyroOffset = rIn.gyroAngle;
		}
		if(CTRL_GYRO_ROT_CCW){ // need to latch mechanism
			gyroOffset += PI / 2.0f;
		}
		if(CTRL_GYRO_ROT_CW){
			gyroOffset -= PI / 2.0f;
		}

		float gyroAngle = PMod(rIn.gyroAngle - gyroOffset, PI*2.0f);
		fieldCentricControl(rOut, CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT, gyroAngle);
		break; }
	case robotCentric:
		robotCentricControl(rOut, CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT);
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
	float bl = transY - transX + rot;
	float br = transY + transX + rot;
	float fl = -transY + transX + rot;
	float fr = -transY - transX + rot;

	rOut.driveBL = SOut(Trunc(bl));
	rOut.driveBR = SOut(Trunc(br));
	rOut.driveFL = SOut(Trunc(fl));
	rOut.driveFR = SOut(Trunc(fr));
}
