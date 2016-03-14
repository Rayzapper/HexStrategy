#ifndef SHAPE_H
#define SHAPE_H

#include <math.h>

class Shape
{
public:
	virtual ~Shape();
	virtual float GetArea() const = 0;
	virtual float GetCircumference() const = 0;
};

#endif