#include "Key.h"
#include <Arduino.h>

Key::Key(){
	const int buttonPin = ; //the number of the push button pin
	const int relayPin = ; //the number of the relay pin 
	const int buttonState = 0; //variable that will change as button is pushed

	void setup() {

		//initialize buttonPin as the input
		pinmode(buttonPin, INPUT);
		//initialize relayPin as the output to solenoid
		pinmode(relayPin, OUTPUT);

	}

	void loop() {

		buttonState = digitalRead(buttonPin);
		if (buttonState == HIGH) {
			digitalWrite(relayPin,HIGH);

		}
	}
}

void Key::periodic(const RobotIn& rIn, RobotOut& rOut){
	
}
