#include "SchoolSystem.h"
#include "Course.h"
#include "Student.h"
#include <iostream>

int main()
{
	Course *course1 = new Course("Math");
	Course *course2 = new Course("Geography");
	Course *course3 = new Course("English");
	Course *course4 = new Course("Physics");
	Course *course5 = new Course("Chemistry");
	Student *student1 = new Student("Philip");
	Student *student2 = new Student("John");
	Student *student3 = new Student("Lisa");
	Student *student4 = new Student("Jenny");
	Student *student5 = new Student("Rob");

	SchoolSystem &schoolSystem = SchoolSystem::GetInstance();
	schoolSystem.AddCourse(course1);
	schoolSystem.AddCourse(course2);
	schoolSystem.AddCourse(course3);
	schoolSystem.AddCourse(course4);
	schoolSystem.AddCourse(course5);
	schoolSystem.AddStudent(student1);
	schoolSystem.AddStudent(student2);
	schoolSystem.AddStudent(student3);
	schoolSystem.AddStudent(student4);
	schoolSystem.AddStudent(student5);

	schoolSystem.Assign(student1, course1);
	schoolSystem.Assign(student1, course3);
	schoolSystem.Assign(student1, course4);

	schoolSystem.Assign(student2, course1);
	schoolSystem.Assign(student2, course2);
	schoolSystem.Assign(student2, course4);
	schoolSystem.Assign(student2, course5);

	schoolSystem.Assign(student3, course1);
	schoolSystem.Assign(student3, course2);
	schoolSystem.Assign(student3, course3);
	schoolSystem.Assign(student3, course4);
	schoolSystem.Assign(student3, course5);

	schoolSystem.Assign(student4, course5);

	schoolSystem.Assign(student5, course1);
	schoolSystem.Assign(student5, course5);

	typedef SchoolSystem::CourseSet CourseSet;
	typedef SchoolSystem::StudentSet StudentSet;

	const CourseSet &courses = schoolSystem.GetCourseSet();
	for (CourseSet::const_iterator i = courses.begin(); i != courses.end(); i++)
	{
		Course *course = *i;
		cout << "Students enrolled in " <<course->GetName() << ":" << endl;
		const StudentSet &students = schoolSystem.GetStudentSet(course);
		for (StudentSet::const_iterator j = students.begin(); j != students.end(); j++)
		{
			Student *student = *j;
			cout << " " << student->GetName() << endl;
		}
	}

	const StudentSet &students2 = schoolSystem.GetStudentSet();
	for (StudentSet::const_iterator i = students2.begin(); i != students2.end(); i++)
	{
		Student *student = *i;
		cout << student->GetName() << " is enrolled in the following courses:" << endl;
		const CourseSet &courses2 = schoolSystem.GetCourseSet(student);
		for (CourseSet::const_iterator j = courses2.begin(); j != courses2.end(); j++)
		{
			Course *course = *j;
			cout << " " << course->GetName() << endl;
		}
	}

	schoolSystem.Clear();
	return 0;
}