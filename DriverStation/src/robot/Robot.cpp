#include "Robot.h"

Robot::Robot() :
	drive(DRIVE_MODE)
{
	
}

void Robot::periodic(const RobotIn& rIn, RobotOut& rOut){
	drive.periodic(rIn, rOut);
}
