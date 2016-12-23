#include <SFML/Graphics.hpp>
#include "gui/gui.h"
#include "gui/appRes.h"
#include "utils/Comms.h"
#include "robot/Robot.h"
#include "robot/RobotIO.h"
using namespace sf;

AppRes* appRes;

int main(){
	RenderWindow window(VideoMode(1000, 632), "Transfarmers Driver Station");

	AppRes res;
	appRes = &res;
	GUI gui;
	Comms comms;
	Robot robot;

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::Resized){
				Vector2u size = window.getSize();
				View view = View(FloatRect(0.0f, 0.0f, (float)size.x, (float)size.y));
				window.setView(view);
			}
		}

		comms.read();
		robot.periodic(comms.in, comms.out);
		comms.write();

		gui.update(window);
		window.clear(Color(24,24,24));
		window.draw(gui);
		window.display();
	}

	return 0;
}
