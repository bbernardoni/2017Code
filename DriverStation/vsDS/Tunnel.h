#ifndef TUNNEL_H
#define TUNNEL_H

#include"Controls.h"
#include"RobotIO.h"
#include<NewPing.h>

#define TRIGGER_PIN_1
#define ECHO_PIN_1
#define TRIGGER_PIN_2
#define ECHO_PIN_2
#define TRIGGER_PIN_3
#define ECHO_PIN_3
#define TRIGGER_PIN_4
#define ECHO_PIN_4
#define MAX_DISTANCE   //constants to be defined
#define BLOCK_DISTANCE

class Tunnel{
public:
	enum direction {direction1, direction2, direction3, direction4};
	void periodic();

private:
	Tunnel(direction d);
	NewPing* sonar[4];
	direction currentDirection();
	direction getNextD();
	direction state;
	bool isBlocked(int dir);


};




#endif