#include "Student.h"

Student::Student(string name)
	: mName(name)
{
}

void Student::SetName(const string &name)
{
	mName = name;
}

const string& Student::GetName() const
{
	return mName;
}