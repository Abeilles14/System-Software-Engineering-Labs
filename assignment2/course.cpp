#include "course.h"


Course::Course() {
	this->Reset();
}
Course::Course(UINT courseNumber, char* courseName, UINT courseNameLength) {
	this->Reset();

	SetCourseNumber(courseNumber);
	SetCourseName(courseName, courseNameLength);
}

// Accessors
void Course::DisplayCourseInfo() const {
	cout << courseNumber << ": " << courseName << std::endl;
}
UINT Course::GetCourseNumber() const {
	cout << courseNumber << std::endl;
	return courseNumber;
}

const char* Course::GetCourseName() const {
	return this->courseName;
}

void Course::DisplayStudentList() const {
	for (UINT index = 0; index < this->studentList.size(); index++) {
		cout << studentList[index]->GetName() << endl;
	}
}
void Course::DisplayAssignments() const {
	for (UINT index = 0; index < this->assignments.size(); index++) {
		cout << assignments[index] << std::endl;
	}
}

// Mutators
bool Course::AddStudent(Student* thisStudent) {
	// Check for prereqs

	if (preReqCourseId == NONE) {
		this->studentList.push_back(thisStudent);
		return true;
	}

	for (UINT index = 0; index < thisStudent->GetGradesList()->size(); index++) {
		if (preReqCourseId == thisStudent->GetGradesList()->at(index).courseNumber) {
			this->studentList.push_back(thisStudent);
			return true;
		}
	}

	cout << "Student does not meet prereq" << endl;
	return false;
}
bool Course::RemoveStudent(UINT studentId) {
	for (UINT index = 0; index < this->studentList.size(); index++) {
		if (studentList[index]->GetUserId() == studentId) {
			studentList.erase(studentList.begin() + index);
			return true;
		}
	}
	return false;
}
bool Course::AddAssignment(string assignment) {
	this->assignments.push_back(assignment);
	return true;
}

bool Course::RemoveAssignment(string assignment) {
	for (UINT index = 0; index < this->assignments.size(); index++) {
		if (assignment == assignments[index]) {
			assignments.erase(assignments.begin() + index);
			return true;
		}
	}
	return false;
}

bool Course::SetCourseNumber(UINT courseNumber) {
	this->courseNumber = courseNumber;
	return true;
}

bool Course::SetCourseName(char* courseName, UINT courseNameLength) {
	memcpy(this->courseName, courseName, courseNameLength);
	return true;
}

bool Course::SetPrereqCourseId(UINT courseId) {
	this->preReqCourseId = courseId;
	return true;
}

// Helpers
void Course::Reset() {
	courseNumber = 0;
	memset(courseName, 0, 9);
	preReqCourseId = NONE;
}
