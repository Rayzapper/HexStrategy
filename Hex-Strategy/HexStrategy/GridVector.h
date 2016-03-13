#ifndef GRIDVECTOR_H
#define GRIDVECTOR_H

class GridVector
{
public:
	GridVector(int x, int y);
	GridVector& operator=(const GridVector &gridVector);
	GridVector& operator+(const GridVector &gridVector);
	GridVector& operator-(const GridVector &gridVector);
	int GetX() const;
	int GetY() const;
	void SetX(int x);
	void SetY(int y);
private:
	int mX, mY;
};

bool operator==(const GridVector &gridVector1, const GridVector &gridVector2);
bool operator!=(const GridVector &gridVector1, const GridVector &gridVector2);

#endif