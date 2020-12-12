#pragma once

#include "constants.h"
#include "student.h"

class Course {
private:
	UINT courseNumber;
	char courseName[9];
	UINT preReqCourseId;
	vector<Student*> studentList;
	vector<string> assignments;

public:
	Course();
	Course(UINT courseNumber, char* courseName, UINT courseNameLength);

	// Accessors
	void DisplayCourseInfo() const;
	UINT GetCourseNumber() const;
	const char* GetCourseName() const;
	void DisplayStudentList() const;
	void DisplayAssignments() const;

	// Mutators
	bool AddStudent(Student* thisStudent);
	bool RemoveStudent(UINT studentId);
	bool AddAssignment(string assignment);
	bool RemoveAssignment(string assignment);

	bool SetCourseNumber(UINT courseNumber);
	bool SetCourseName(char* courseName, UINT courseNameLength);
	bool SetPrereqCourseId(UINT courseId);


	// Helpers
	void Reset();

};