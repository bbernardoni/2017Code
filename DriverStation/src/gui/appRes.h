#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

struct AppRes {
	AppRes(){
		arial.loadFromFile("../../res/arial.ttf");
	};

	Font arial;
};