#ifndef TRIANGLETOOL_H
#define TRIANGLETOOL_H

class Shape;

struct TriangleTool
{
	static Shape* CreateTriangle(float side1, float side2, float side3);
	static Shape* CreateAcuteTriangle(float side);
	static Shape* CreateRightTriangle(float height, float base);
};

#endif