#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "gElem.h"
#include "textOut.h"
#include "appRes.h"
using namespace sf;

extern AppRes* appRes;

class Console: public GElem {
public:
	Console();
	void scroll(Event::MouseWheelScrollEvent event);

private:
	RenderTexture rt;
	Text conTxt;
	Vector2f oldSize;
};
