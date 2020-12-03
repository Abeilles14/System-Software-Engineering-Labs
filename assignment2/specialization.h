#pragma once

#include "constants.h"
#include "student.h"

class Specialization {
private:
	UINT specializationNumber;
	char specializationName[9];
	vector<courseBase> enrolledCourses;
	UINT averageGrade;

public:
	Specialization();
	Specialization(UINT specializationNumber, char* specializationName, UINT specializationNameLength, UINT averageGrade);

	// Accessors
	void DisplaySpecializationInfo() const;
	UINT GetSpecializationNumber() const;
	const char* GetSpecializationName() const;
	const vector<courseBase>* GetEnrolledCourses() const;
	UINT GetAverageGrade() const;

	// Mutators
	bool SetSpecializationNumber(UINT specializatinoNumber);
	bool AddEnrolledCourse(courseBase enrolledCourse);
	bool SetSpecializationName(char* specializationName, UINT specializationNameLength);
	bool SetAverageGrade(UINT averageGrade);

	// Helpers
	void Reset();

};