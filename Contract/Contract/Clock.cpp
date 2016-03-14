#include "Clock.h"
#include <cassert>

Clock::Clock(int startHour, int startMinute)
	: mHour(startHour),
	mMinute(startMinute)
{
	assert(0 <= startHour && startHour <= 23 && 0 <= startMinute && startMinute <= 59);
	assert(mHour == startHour && mMinute == startMinute);
	assert(invariant());
}

Clock::Clock(const Clock &clock)
	: mHour(clock.mHour),
	mMinute(clock.mMinute)
{
	assert(mHour == clock.mHour && mMinute == clock.mMinute);
	assert(invariant());
}

Clock::~Clock()
{
	assert(invariant());
}

Clock& Clock::operator=(const Clock &clock)
{
	assert(invariant());
	mHour = clock.mHour;
	mMinute = clock.mMinute;
	assert(invariant());
	return *this;
}

string Clock::Read() const
{
	assert(invariant());
	string hour, minute;
	if (mHour < 10)
		hour = "0" + to_string(mHour);
	else
		hour = to_string(mHour);
	if (mMinute < 10)
		minute = "0" + to_string(mMinute);
	else
		minute = to_string(mMinute);
	return hour + ":" + minute;
}

int Clock::GetMinute() const
{
	assert(invariant());
	return mMinute;
}

int Clock::GetHour() const
{
	assert(invariant());
	return mHour;
}

void Clock::SetMinute(int minute)
{
	assert(invariant());
	assert(0 <= minute);
	mMinute = minute;
	assert(mMinute == minute);
	assert(invariant());
}

void Clock::SetHour(int hour)
{
	assert(invariant());
	assert(0 <= hour);
	mHour = hour;
	assert(mHour == hour);
	assert(invariant());
}

void Clock::ForwardMinutes(int minutes)
{
	assert(invariant());
	assert(0 <= minutes);
	int oldMinute = mMinute;
	assert(oldMinute == mMinute);
	mMinute += minutes;
	assert(mMinute == oldMinute + minutes);
	int counter = 0;
	assert(counter == 0);
	while (mMinute >= 60)
	{
		counter++;
		assert(mMinute >= 60);
		oldMinute = mMinute;
		assert(oldMinute == mMinute);
		mMinute -= 60;
		assert(mMinute == oldMinute - 60);
	}
	ForwardHours(counter);
	assert(invariant());
}

void Clock::RewindMinutes(int minutes)
{
	assert(invariant());
	assert(0 <= minutes);
	int oldMinute = mMinute;
	assert(oldMinute == mMinute);
	mMinute -= minutes;
	assert(mMinute == oldMinute - minutes);
	int counter = 0;
	assert(counter == 0);
	while (mMinute < 0)
	{
		counter++;
		assert(mMinute < 0);
		oldMinute = mMinute;
		assert(oldMinute == mMinute);
		mMinute += 60;
		assert(mMinute == oldMinute + 60);
	}
	RewindHours(counter);
	assert(invariant());
}

void Clock::ForwardHours(int hours)
{
	assert(invariant());
	assert(0 <= hours);
	int oldHour = mHour;
	assert(oldHour == mHour);
	mHour += hours;
	assert(mHour == oldHour + hours);
	while (mHour >= 24)
	{
		assert(mHour >= 24);
		oldHour = mHour;
		assert(oldHour == mHour);
		mHour -= 24;
		assert(mHour == oldHour - 24);
	}
	assert(invariant());
}

void Clock::RewindHours(int hours)
{
	assert(invariant());
	assert(0 <= hours);
	int oldHour = mHour;
	assert(oldHour == mHour);
	mHour -= hours;
	assert(mHour == oldHour - hours);
	while (mHour < 0)
	{
		assert(mHour < 0);
		oldHour = mHour;
		assert(oldHour == mHour);
		mHour += 24;
		assert(mHour == oldHour + 24);
	}
	assert(invariant());
}

bool Clock::invariant() const
{
	return 0 <= mHour && mHour <= 23 && 0 <= mMinute && mMinute <= 59;
}

bool operator==(const Clock &clock1, const Clock &clock2)
{
	return clock1.GetHour() == clock2.GetHour() && clock1.GetMinute() == clock2.GetMinute();
}

bool operator!=(const Clock &clock1, const Clock &clock2)
{
	return clock1.GetHour() != clock2.GetHour() || clock1.GetMinute() != clock2.GetMinute();
}