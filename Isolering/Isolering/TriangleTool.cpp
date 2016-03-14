#include "TriangleTool.h"
#include "Triangle.h"

Shape* TriangleTool::CreateTriangle(float side1, float side2, float side3)
{
	return new Triangle(side1, side2, side3);
}

Shape* TriangleTool::CreateAcuteTriangle(float side)
{
	return new Triangle(side, side, side);
}

Shape* TriangleTool::CreateRightTriangle(float height, float base)
{
	return new Triangle(height, base, hypotf(height, base));
}