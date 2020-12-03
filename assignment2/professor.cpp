#include "professor.h"

Professor::Professor() {
	this->Reset();
}
Professor::Professor(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength) {
	this->Reset();

	this->InitializeUser(userId, name, nameLength, userTypes::typeProfessor, userName, usernameLength, password, passwordLength);
}

// Accessors
void Professor::DisplayCourseList() const {
	for (UINT index = 0; index < this->courseList.size(); index++) {
		this->courseList[index]->DisplayCourseInfo();
	}
}

// Mutators
bool Professor::AddCourse(Course* course) {
	this->courseList.push_back(course);		//TODO: fix bug
	cout << "Professor Added to Course";
	return true;
}

bool Professor::RemoveCourse(UINT courseId) {
	for (UINT index = 0; index < this->courseList.size(); index++) {
		if (this->courseList[index]->GetCourseNumber() == courseId) {
			this->courseList.erase(this->courseList.begin() + index);
			cout << "Professor Unassigned To Course";
			return true;
		}
	}

	cout << "Error Unassigning Professor To Course";
	return false;
}

// Helpers
void Professor::Reset() {
	User::Reset();

	this->courseList.clear();
}