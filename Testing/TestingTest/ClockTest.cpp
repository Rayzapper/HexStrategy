#include "ClockTest.h"
#include "Clock.h"
#include <cassert>

using namespace std;

void ClockTest::Run()
{
	Clock clock0;
	assert(clock0.GetHour() == 0);
	assert(clock0.GetMinute() == 0);

	Clock clock1(7, 30);
	assert(clock1.GetHour() == 7);
	assert(clock1.GetMinute() == 30);

	Clock clock2(clock1);
	assert(clock2.GetHour() == 7);
	assert(clock2.GetMinute() == 30);

	Clock clock3;
	clock3 = clock2;
	assert(clock3.GetHour() == 7);
	assert(clock3.GetMinute() == 30);

	Clock clock4(2, 50);
	clock4.SetHour(4);
	assert(clock4.GetHour() == 4);
	clock4.SetMinute(15);
	assert(clock4.GetMinute() == 15);

	Clock clock5(4, 20);
	clock5.ForwardHours(2);
	assert(clock5.GetHour() == 6);
	clock5.ForwardHours(20);
	assert(clock5.GetHour() == 2);

	Clock clock6(9, 20);
	clock6.RewindHours(2);
	assert(clock6.GetHour() == 7);
	clock6.RewindHours(10);
	assert(clock6.GetHour() == 21);

	Clock clock7(4, 40);
	clock7.ForwardMinutes(5);
	assert(clock7.GetMinute() == 45);
	clock7.ForwardMinutes(90);
	assert(clock7.GetMinute() == 15);
	assert(clock7.GetHour() == 6);

	Clock clock8(22, 20);
	clock8.RewindMinutes(5);
	assert(clock8.GetMinute() == 15);
	clock8.RewindMinutes(20);
	assert(clock8.GetMinute() == 55);
	assert(clock8.GetHour() == 21);

	Clock clockA0(0, 0);
	Clock clockA1(0, 0);
	Clock clockB0(0, 1);
	Clock clockB1(0, 1);
	Clock clockC0(1, 0);
	Clock clockC1(1, 0);
	Clock clockD0(1, 1);
	Clock clockD1(1, 1);
	assert(clockA0 == clockA1);
	assert(clockB0 == clockB1);
	assert(clockC0 == clockC1);
	assert(clockD0 == clockD1);
	assert(clockA0 != clockB0);
	assert(clockA0 != clockC0);
	assert(clockA0 != clockD0);
}