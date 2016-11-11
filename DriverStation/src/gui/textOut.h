#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "gElem.h"
#include "joyPanel.h"
using namespace sf;

extern Font arial;

class TextOut: public GElem {
public:
	TextOut();

	void setLabel(String s);
	enum CtrType{button, axis, pov};
	void setJoyLoc(int loc, CtrType tp);

	void update(GElem* parent);
private:
	String label;
	int joyLoc;
	CtrType type;
	String output;
};
