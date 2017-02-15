#include "Tunnel.h"

Tunnel::Tunnel(direction d){
	sonar[0] = new NewPing(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
	sonar[1] = new NewPing(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
	sonar[2] = new NewPing(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);
	sonar[3] = new NewPing(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
	state = d;
}

void Tunnel::periodic(){
	switch (state){
	case direction1:
		/*move in direction1*/
		if (isBlocked(1)) state = getNextD();
		break;
	case direction2:
		/*move in direction2*/
		if (isBlocked(2)) state = getNextD();
		break;
	case direction3:
		/*move in direction3*/
		if (isBlocked(3)) state = getNextD();
		break;
	case direction4:
		/*move in direction4*/
		if (isBlocked(4)) state = getNextD();
		break;
	}



}

Tunnel::direction Tunnel::getNextD(){
	if (state == direction1){
		if (isBlocked(2)) return direction4;
		else return direction2;
	}
	if (state == direction2){
		if (isBlocked(1)) return direction3;
		else return direction1;
	}
	if (state == direction3){
		if (isBlocked(2)) return direction4;
		else return direction2;
	}
	if (state == direction4){
		if (isBlocked(1)) return direction3;
		else return direction1;
	}
}

Tunnel::direction Tunnel::currentDirection(){
	return state;
}

bool Tunnel::isBlocked(int dir){
	if (sonar[dir - 1].ping_in() < BLOCK_DISTANCE) return true;
	return false;
}