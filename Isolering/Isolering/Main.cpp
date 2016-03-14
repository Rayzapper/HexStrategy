#include "CircleTool.h"
#include "RectangleTool.h"
#include "TriangleTool.h"
#include "Shape.h"
#include <iostream>

using namespace std;

int main()
{
	Shape *circle = CircleTool::CreateCircle(10);
	cout << "Circle with radius 10, Area = " << circle->GetArea() << " square units" << endl;
	cout << "Circle with radius 10, Circumference = " << circle->GetCircumference() << " units" << endl;

	Shape *rectangle1 = RectangleTool::CreateRectangle(10, 15);
	cout << "Rectangle with the sides 10 and 15, Area = " << rectangle1->GetArea() << " square units" << endl;
	cout << "Rectangle with the sides 10 and 15, Circumference = " << rectangle1->GetCircumference() << " units" << endl;

	Shape *rectangle2 = RectangleTool::CreateSquare(5);
	cout << "Square with sides 5, Area = " << rectangle2->GetArea() << " square units" << endl;
	cout << "Square with sides 5, Circumference = " << rectangle2->GetCircumference() << " units" << endl;

	Shape *triangle1 = TriangleTool::CreateTriangle(15, 4, 12);
	cout << "Triangle with the sides 15, 4 and 12, Area = " << triangle1->GetArea() << " square units" << endl;
	cout << "Triangle with the sides 15, 4 and 12, Circumference = " << triangle1->GetCircumference() << " units" << endl;

	Shape *triangle2 = TriangleTool::CreateAcuteTriangle(9);
	cout << "Acute triangle with sides 9, Area = " << triangle2->GetArea() << " square units" << endl;
	cout << "Acute triangle with sides 9, Circumference = " << triangle2->GetCircumference() << " units" << endl;

	Shape *triangle3 = TriangleTool::CreateRightTriangle(10, 10);
	cout << "Right triangle with the height 10 and the base 10, Area = " << triangle3->GetArea() << " square units" << endl;
	cout << "Right triangle with the height 10 and the base 10, Circumference = " << triangle3->GetCircumference() << " units" << endl;
	return 0;
}