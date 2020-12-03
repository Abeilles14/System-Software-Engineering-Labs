#pragma once

#include "user.h"
#include "course.h"

using namespace std;

class Professor : public User {
private:
	vector<Course*> courseList;

public:
	Professor();
	Professor(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength);

	// Accessors
	void DisplayCourseList() const;

	// Mutators
	bool AddCourse(Course* course);
	bool RemoveCourse(UINT courseId);

	// Helpers
	void Reset();

};