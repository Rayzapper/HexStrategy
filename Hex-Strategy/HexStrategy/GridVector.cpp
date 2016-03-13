#include "GridVector.h"

GridVector::GridVector(int x, int y)
	: mX(x), mY(y)
{

}

GridVector& GridVector::operator=(const GridVector &gridVector)
{
	mX = gridVector.mX;
	mY = gridVector.mY;
	return *this;
}

GridVector& GridVector::operator+(const GridVector &gridVector)
{
	mX += gridVector.mX;
	mY += gridVector.mY;
	return *this;
}

GridVector& GridVector::operator-(const GridVector &gridVector)
{
	mX -= gridVector.mX;
	mY -= gridVector.mY;
	return *this;
}

int GridVector::GetX() const
{
	return mX;
}

int GridVector::GetY() const
{
	return mY;
}

void GridVector::SetX(int x)
{
	mX = x;
}

void GridVector::SetY(int y)
{
	mY = y;
}

bool operator==(const GridVector &gridVector1, const GridVector &gridVector2)
{
	return gridVector1.GetX() == gridVector2.GetX() && gridVector1.GetY() == gridVector2.GetY();
}

bool operator!=(const GridVector &gridVector1, const GridVector &gridVector2)
{
	return gridVector1.GetX() != gridVector2.GetX() || gridVector1.GetY() != gridVector2.GetY();
}