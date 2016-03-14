#include "Circle.h"

Circle::Circle(float radius)
	: mRadius(radius)
{
}

float Circle::GetArea() const
{
	float area = mRadius * mRadius * 3.1415926;
	return area;
}

float Circle::GetCircumference() const
{
	float circumference = mRadius * 2 * 3.1415926;
	return circumference;
}