#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(float side1, float side2, float side3);
	virtual float GetArea() const;
	virtual float GetCircumference() const;
private:
	float mSide1, mSide2, mSide3;
};

#endif