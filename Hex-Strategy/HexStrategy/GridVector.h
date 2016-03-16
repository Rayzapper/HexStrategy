#ifndef GRIDVECTOR_H
#define GRIDVECTOR_H

struct GridVector
{
	GridVector();
	GridVector(int X, int Y);
	GridVector& operator=(const GridVector &gridVector);
	GridVector& operator+(const GridVector &gridVector);
	GridVector& operator-(const GridVector &gridVector);
	int x, y;
};

bool operator==(const GridVector &gridVector1, const GridVector &gridVector2);
bool operator!=(const GridVector &gridVector1, const GridVector &gridVector2);

#endif