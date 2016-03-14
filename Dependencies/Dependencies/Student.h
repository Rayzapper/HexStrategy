#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student
{
public:
	Student(string name);
	void SetName(const string &name);
	const string& GetName() const;
private:
	string mName;
};

#endif