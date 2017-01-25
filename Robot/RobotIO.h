#pragma once

struct RobotIn{
  float gyroAngle;

  RobotIn() :
    gyroAngle(0.0f)
  {}
};

struct RobotOut{
  char driveFL;
  char driveBL;
  char driveFR;
  char driveBR;
  bool omni;

  RobotOut() :
    driveFL(90),
    driveBL(90),
    driveFR(90),
    driveBR(90),
    omni(false)
  {}
};


