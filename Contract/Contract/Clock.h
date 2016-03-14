#ifndef CLOCK_H
#define CLOCK_H

#include <string>

using namespace std;

class Clock
{
public:
	Clock(int startHour = 0, int startMinute = 0);
	Clock(const Clock &clock);
	~Clock();
	Clock& operator=(const Clock &clock);
	string Read() const;
	int GetMinute() const;
	int GetHour() const;
	void SetMinute(int minute);
	void SetHour(int hour);
	void ForwardMinutes(int minutes);
	void RewindMinutes(int minutes);
	void ForwardHours(int hours);
	void RewindHours(int hours);
private:
	bool invariant() const;
	int mHour;
	int mMinute;
};

bool operator==(const Clock &clock1, const Clock &clock2);
bool operator!=(const Clock &clock1, const Clock &clock2);

#endif