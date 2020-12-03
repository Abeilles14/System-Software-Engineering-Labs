#include "specialization.h"


Specialization::Specialization() {
	this->Reset();
}
Specialization::Specialization(UINT specializationNumber, char* specializationName, UINT specializationNameLength, UINT averageGrade) {
	this->Reset();

	SetSpecializationNumber(specializationNumber);
	//SetEnrolledCourse(enrolledCourses);
	SetSpecializationName(specializationName, specializationNameLength);
	SetAverageGrade(averageGrade);
}

// Accessors
void Specialization::DisplaySpecializationInfo() const {
	cout << specializationNumber << ": " << specializationName << std::endl;
}

UINT Specialization::GetSpecializationNumber() const {
	cout << specializationNumber << std::endl;
	return specializationNumber;
}

const vector<courseBase>* Specialization::GetEnrolledCourses() const {
	return &this->enrolledCourses;
}

UINT Specialization::GetAverageGrade() const {
	return this->averageGrade;
}

const char* Specialization::GetSpecializationName() const {
	return this->specializationName;
}

// Mutators
bool Specialization::SetSpecializationNumber(UINT specializatinoNumber) {
	this->specializationNumber = specializationNumber;
	return true;
}

bool Specialization::AddEnrolledCourse(courseBase enrolledCourse) {
	this->enrolledCourses.push_back(enrolledCourse);
	return true;
}

bool Specialization::SetSpecializationName(char* specializationName, UINT specializationNameLength) {
	memcpy(this->specializationName, specializationName, specializationNameLength);
	return true;
}

bool Specialization::SetAverageGrade(UINT averageGrade) {
	this->averageGrade = averageGrade;
	return true;
}


// Helpers
void Specialization::Reset() {
	specializationNumber = 0;
	memset(specializationName, 0, 9);
	averageGrade = 0;
}
