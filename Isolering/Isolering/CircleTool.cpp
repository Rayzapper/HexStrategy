#include "CircleTool.h"
#include "Circle.h"

Shape* CircleTool::CreateCircle(float radius)
{
	return new Circle(radius);
}