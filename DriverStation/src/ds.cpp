#include <SFML/Graphics.hpp>
#include "gui/gui.h"
using namespace sf;

Font arial;

int main(){
	RenderWindow window(VideoMode(1280, 720), "Transfarmers Driver Station");
	arial.loadFromFile("res/arial.ttf");

	GUI gui;

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::Resized){
				Vector2u size = window.getSize();
				View view = View(FloatRect(0.0f, 0.0f, size.x, size.y));
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
