#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

struct AppRes {
	AppRes(){
		if(!arial.loadFromFile("arial.ttf"))
			arial.loadFromFile("../../res/arial.ttf");
	};

	Font arial;
};