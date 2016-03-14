#ifndef COURSE_H
#define COURSE_H

#include <string>

using namespace std;

class Course
{
public:
	Course(string name);
	void SetName(const string &name);
	const string& GetName() const;
private:
	string mName;
};

#endif