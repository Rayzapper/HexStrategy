#ifndef SCHOOLSYSTEM_H
#define SCHOOLSYSTEM_H

#include <set>
#include <map>

using namespace std;

class Student;
class Course;

class SchoolSystem
{
public:
	typedef set<Student*> StudentSet;
	typedef set<Course*> CourseSet;
	void AddStudent(Student *student);
	void AddCourse(Course *course);
	void Assign(Student *student, Course *course);
	void Unassign(Student *student, Course *course);
	void Clear();
	CourseSet& GetCourseSet();
	CourseSet& GetCourseSet(Student *student);
	StudentSet& GetStudentSet();
	StudentSet& GetStudentSet(Course *course);
	static SchoolSystem& GetInstance();
private:
	SchoolSystem();
	SchoolSystem(const SchoolSystem &schoolSystem);
	SchoolSystem& operator=(const SchoolSystem &schoolSystem);
	~SchoolSystem();
	void InternalClear();
	StudentSet mStudentSet;
	CourseSet mCourseSet;
	map<Student*, CourseSet> mStudentToCourses;
	map<Course*, StudentSet> mCourseToStudents;
};

#endif