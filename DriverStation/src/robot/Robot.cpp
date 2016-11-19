#include "Robot.h"

Robot::Robot(Drive::DriveMode _mode) :
	drive(_mode)
{
	
}

void Robot::periodic(const RobotIn& rIn, RobotOut& rOut){
	drive.periodic(rIn, rOut);
}
