#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(float sideX, float sideY);
	virtual float GetArea() const;
	virtual float GetCircumference() const;
private:
	float mSideX;
	float mSideY;
};

#endif