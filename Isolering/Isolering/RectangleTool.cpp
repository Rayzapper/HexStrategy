#include "RectangleTool.h"
#include "Rectangle.h"

Shape* RectangleTool::CreateRectangle(float side1, float side2)
{
	return new Rectangle(side1, side2);
}

Shape* RectangleTool::CreateSquare(float side)
{
	return new Rectangle(side, side);
}