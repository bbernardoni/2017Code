#pragma once

#include <SFML/Graphics.hpp>
#include "gElem.h"
#include "joyPanel.h"
#include "console.h"
using namespace sf;

class GUI: public GElem {
public:
	GUI();
	
	void update(const RenderWindow& window);
	void scroll(Event::MouseWheelScrollEvent event);

private:
	using GElem::update;
	Console* console;
};
