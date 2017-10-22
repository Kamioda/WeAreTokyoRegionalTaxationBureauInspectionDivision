#pragma once
#include "Graphic.h"

class VirtualChildWindow {
	Box box;
	int x, y, blend_level;
public:
	VirtualChildWindow(const int x, const int y, const Color color, const int blend_level = 100);
	void start();
	void end();
};
