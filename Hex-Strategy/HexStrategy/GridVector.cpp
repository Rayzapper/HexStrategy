#include "GridVector.h"

GridVector::GridVector()
{

}

GridVector::GridVector(int X, int Y)
	: x(X), y(Y)
{

}

GridVector& GridVector::operator=(const GridVector &gridVector)
{
	x = gridVector.x;
	y = gridVector.y;
	return *this;
}

GridVector& GridVector::operator+(const GridVector &gridVector)
{
	x += gridVector.x;
	y += gridVector.y;
	return *this;
}

GridVector& GridVector::operator-(const GridVector &gridVector)
{
	x -= gridVector.x;
	y -= gridVector.y;
	return *this;
}

bool operator==(const GridVector &gridVector1, const GridVector &gridVector2)
{
	return gridVector1.x == gridVector2.x && gridVector1.y == gridVector2.y;
}

bool operator!=(const GridVector &gridVector1, const GridVector &gridVector2)
{
	return gridVector1.x != gridVector2.x || gridVector1.y != gridVector2.y;
}