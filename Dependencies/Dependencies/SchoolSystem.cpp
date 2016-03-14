#include "SchoolSystem.h"
#include "Student.h"
#include "Course.h"
#include <set>
#include <map>

void SchoolSystem::AddStudent(Student *student)
{
	mStudentSet.insert(student);
}

void SchoolSystem::AddCourse(Course *course)
{
	mCourseSet.insert(course);
}

void SchoolSystem::Assign(Student *student, Course *course)
{
	mStudentToCourses[student].insert(course);
	mCourseToStudents[course].insert(student);
}

void SchoolSystem::Unassign(Student *student, Course *course)
{
	mStudentToCourses[student].erase(course);
	mCourseToStudents[course].erase(student);
}

void SchoolSystem::Clear()
{
	InternalClear();
}

SchoolSystem::CourseSet& SchoolSystem::GetCourseSet()
{
	return mCourseSet;
}

SchoolSystem::CourseSet& SchoolSystem::GetCourseSet(Student *student)
{
	return mStudentToCourses.find(student)->second;
}

SchoolSystem::StudentSet& SchoolSystem::GetStudentSet()
{
	return mStudentSet;
}

SchoolSystem::StudentSet& SchoolSystem::GetStudentSet(Course *course)
{
	return mCourseToStudents.find(course)->second;
}

SchoolSystem& SchoolSystem::GetInstance()
{
	static SchoolSystem schoolSystem;
	return schoolSystem;
}

SchoolSystem::SchoolSystem()
{

}

SchoolSystem::~SchoolSystem()
{
	InternalClear();
}

void SchoolSystem::InternalClear()
{
	mStudentToCourses.clear();
	mCourseToStudents.clear();
	while (!mStudentSet.empty())
	{
		Student *student = *mStudentSet.begin();
		mStudentSet.erase(student);
		delete student;
	}
	while (!mCourseSet.empty())
	{
		Course *course = *mCourseSet.begin();
		mCourseSet.erase(course);
		delete course;
	}
}