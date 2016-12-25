#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string.h>
#include "gElem.h"
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

	void toClipboard(const String &str);
};
