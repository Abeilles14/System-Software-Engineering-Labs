#pragma once

#include "user.h"

using namespace std;

class Student : public User {
private:
	vector<grade> studentGrades;
	char specialization[20];
	UINT tuitionFees;
	vector<courseBase> enrolledCourses;

public:
	Student();
	Student(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength);

	// Accessors
	void DisplayStudentInfo() const;
	void GetGrades() const;
	void GetSpecialization() const;
	UINT GetTuitionFees() const;
	void GetEnrolledCourses() const;
	const vector<grade>* GetGradesList() const;

	// Mutators
	bool AddGrade(grade thisGrade);
	bool SetTuition(UINT tuition);
	bool SetSpecialization(char* specialization, UINT specializationLength);
	bool AddCourse(UINT courseId, const char* courseName, UINT courseNameLength);
	bool RemoveCourse(UINT courseId);
	

	// Helpers
	void Reset();

};