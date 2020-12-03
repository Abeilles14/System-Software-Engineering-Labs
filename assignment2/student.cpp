#include "student.h"

Student::Student() {
	this->Reset();
}

Student::Student(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength) {
	this->Reset();

	this->InitializeUser(userId, name, nameLength, userTypes::typeStudent, userName, usernameLength, password, passwordLength);
}

// Accessors
void Student::DisplayStudentInfo() const {
	cout << "Name: " << this->GetName() << endl;
	cout << "Specialization: " << this->specialization << endl;
	cout << "Fees due: " << this->tuitionFees << endl;
	cout << "Enrolled Courses: " << endl;
	this->GetEnrolledCourses();
	cout << "Grades: " << endl;
	this->GetGrades();
}

void Student::GetGrades() const {
	for (UINT index = 0; index < studentGrades.size(); index++) {
		cout << studentGrades[index].courseName << ": " << studentGrades[index].grade << endl;
	}
}
void Student::GetSpecialization() const {
	cout << this->specialization;
}
UINT Student::GetTuitionFees() const {
	cout << this->tuitionFees;
	return this->tuitionFees;
}
void Student::GetEnrolledCourses() const {
	for (UINT index = 0; index < this->enrolledCourses.size(); index++) {
		cout << enrolledCourses[index].courseNumber << ": " << enrolledCourses[index].courseName << endl;
	}
}

const vector<grade>* Student::GetGradesList() const {
	return &this->studentGrades;
}

// Mutators
bool Student::AddGrade(grade thisGrade) {
	this->studentGrades.push_back(thisGrade);
	return true;
}

bool Student::SetTuition(UINT tuition) {
	this->tuitionFees = tuition;
	return true;
}
bool Student::SetSpecialization(char* specialization, UINT specializationLength) {
	memcpy(this->specialization, specialization, specializationLength);
	return  true;
}
bool Student::AddCourse(UINT courseId, const char* courseName, UINT courseNameLength) {
	courseBase newCourse;
	newCourse.courseNumber = courseId;
	memset(newCourse.courseName, 0, 20);
	memcpy(newCourse.courseName, courseName, courseNameLength);
	this->enrolledCourses.push_back(newCourse);
	return true;
}

bool Student::RemoveCourse(UINT courseId) {
	for (UINT index = 0; index < enrolledCourses.size(); index++) {
		if (enrolledCourses[index].courseNumber = courseId) {
			enrolledCourses.erase(enrolledCourses.begin() + index);
			return true;
		}
	}
	return false;
}

// Helpers

void Student::Reset() {
	User::Reset();

	this->studentGrades.clear();
	SetUserType(userTypes::typeStudent);
	//this->enrolledCourses.clear();
	memset(specialization, 0, 20);
	this->tuitionFees = 0;
}