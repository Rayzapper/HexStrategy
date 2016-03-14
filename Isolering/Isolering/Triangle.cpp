#include "Triangle.h"
#include <iostream>
Triangle::Triangle(float side1, float side2, float side3)
	: mSide1(side1),
	mSide2(side2),
	mSide3(side3)
{
}

float Triangle::GetArea() const
{
	float area, s;
	s = (mSide1 + mSide2 + mSide3) / 2;
	area = (s - mSide1) * (s - mSide2) * (s - mSide3);
	area = area * s;
	area = sqrtf(area);
	return area;
}

float Triangle::GetCircumference() const
{
	float circumference = mSide1 + mSide2 + mSide3;
	return circumference;
}