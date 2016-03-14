#include "Clock.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Creating three clocks, one is set to 15:40, another 00:00 and the last 9:30." << endl;
	Clock clock1(15, 30), clock2(0, 0), clock3(9, 30);
	cout << "Clock 1 reads " << clock1.Read() << "!" << endl;
	cout << "Clock 2 reads " << clock2.Read() << "!" << endl;
	cout << "Clock 3 reads " << clock3.Read() << "!" << endl;
	cout << "Increasing clock 3 by 80 minutes." << endl;
	clock3.ForwardMinutes(80);
	cout << "Clock 3 reads " << clock3.Read() << "!" << endl;
	cout << "Rewinding clock 2 by 5 hours and 15 minutes." << endl;
	clock2.RewindHours(5);
	clock2.RewindMinutes(15);
	cout << "Clock 2 reads " << clock2.Read() << "!" << endl;
	return 0;
}