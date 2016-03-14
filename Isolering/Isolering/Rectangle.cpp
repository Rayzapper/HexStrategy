#include "Rectangle.h"

Rectangle::Rectangle(float sideX, float sideY)
	: mSideX(sideX),
	mSideY(sideY)
{
}

float Rectangle::GetArea() const
{
	float area = mSideX * mSideY;
	return area;
}

float Rectangle::GetCircumference() const
{
	float circumference = mSideX * 2 + mSideY * 2;
	return circumference;
}