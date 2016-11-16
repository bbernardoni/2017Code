#include <SFML/Graphics.hpp>
#include "gui/gui.h"
#include "gui/appRes.h"
using namespace sf;

AppRes* appRes;

int main(){
	RenderWindow window(VideoMode(1280, 720), "Transfarmers Driver Station");

	AppRes res;
	appRes = &res;
	GUI gui;

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
