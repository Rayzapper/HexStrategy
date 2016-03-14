#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape
{
public:
	Circle(float radius);
	virtual float GetArea() const;
	virtual float GetCircumference() const;
private:
	float mRadius;
};

#endif