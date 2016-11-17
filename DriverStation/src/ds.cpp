#include <SFML/Graphics.hpp>
#include "gui/gui.h"
#include "gui/appRes.h"
#include "serial/serial.h"
using namespace sf;
using namespace serial;

AppRes* appRes;

void enumerate_ports(){
	vector<PortInfo> devices_found = list_ports();
	for (vector<PortInfo>::iterator it = devices_found.begin(); it != devices_found.end(); ++it){
		printf("(%s, %s, %s)\n", it->port.c_str(), it->description.c_str(), it->hardware_id.c_str());
	}
}

int main(){
	RenderWindow window(VideoMode(1280, 720), "Transfarmers Driver Station");

	AppRes res;
	appRes = &res;
	GUI gui;

	enumerate_ports();
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

		gui.update(window);

		window.clear(Color(24,24,24));
		window.draw(gui);
		window.display();
	}

	return 0;
}
