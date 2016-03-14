#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

class Shape;

struct RectangleTool
{
	static Shape* CreateRectangle(float side1, float side2);
	static Shape* CreateSquare(float side);
};

#endif