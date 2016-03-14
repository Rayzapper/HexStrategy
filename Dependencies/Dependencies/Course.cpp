#include "Course.h"

Course::Course(string name)
	: mName(name)
{
}

void Course::SetName(const string &name)
{
	mName = name;
}

const string& Course::GetName() const
{
	return mName;
}