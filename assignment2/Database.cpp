#include "database.h"

SystemDatabase::SystemDatabase() {
	this->Reset();
}

SystemDatabase::SystemDatabase(vector<student> studentList, vector<course> courseList) {
	this->Reset();
	this->studentDB = studentList;
	this->courseDB = courseList;
}

void SystemDatabase::Reset() {
	this->studentDB.clear();
	this->courseDB.clear();
}

bool SystemDatabase::GetUser(char* cwlUsername, UINT usernameLength, char* cwlPassword, UINT passwordLength, UINT userId, UINT userType) {
	UINT userSize = this->userDB.size();
	for (UINT index = 0; index < userSize; index++) {
		if (usernameLength != strlen(this->userDB[index].cwlUsername)) {
			continue;
		}

		if (memcmp(cwlUsername, this->userDB[index].cwlUsername, usernameLength) != 0) {
			continue;
		}

		if (passwordLength != strlen(this->userDB[index].cwlPassword)) {
			cout << "Incorrect password\n";
			continue;
		}

		if (memcmp(cwlUsername, this->userDB[index].cwlPassword, passwordLength) != 0) {
			cout << "Incorrect password\n";
			break;
		}
		// User has been found
		userId = this->userDB[index].userId;
		userType = this->userDB[index].userType;
		return true;
	}
	cout << "Unable to login\n";
	return false;
}

// Display course list
void SystemDatabase::GetCourseDatabase() {
	UINT courseSize = this->courseDB.size();
	for (UINT index = 0; index < courseSize; index++) {
		cout << index << ": " << this->courseDB[index].courseName << std::endl;
	}
}

// Display student list
void SystemDatabase::GetStudentDatabase() {
	UINT studentSize = this->studentDB.size();
	for (UINT index = 0; index < studentSize; index++) {
		cout << this->studentDB[index].name << std::endl;
	}
}

void SystemDatabase::GetCourseInfo(UINT courseId) {
	// Package course info
	if (courseId < this->courseDB.size()) {
		return;
	}

	cout << this->courseDB[courseId].courseName;
	cout << "List of students enrolled by ID number:\n";
	for (UINT index = 0; index < this->courseDB[courseId].studentList.size(); index++) {
		cout << this->courseDB[courseId].studentList[index];
	}

	cout << "List of assignments:\n";
	for (UINT index = 0; index < this->courseDB[courseId].assignments.size(); index++) {
		cout << this->courseDB[courseId].assignments[index];
	}
}

void SystemDatabase::GetStudentInfo(UINT userId) {
	if (userId < this->studentDB.size()) {
		return;
	}
	cout << this->studentDB[userId].name << std::endl;
	cout << this->studentDB[userId].specialization << std::endl;
	cout << "Courses:\n";
	for (UINT index = 0; index < this->studentDB[userId].courseList.size(); index++) {
		cout << this->studentDB[userId].courseList[index] << std::endl;
	}
	cout << "Grades:\n";
	for (UINT index = 0; index < this->studentDB[userId].gradesList.size(); index++) {
		cout << this->studentDB[userId].gradesList[index].courseId << ": " << this->studentDB[userId].gradesList[index].grade << std::endl;
	}
}
void GetStudentRequests();

bool SystemDatabase::EnrollInCourse(UINT userId, UINT courseId) {
	if (courseId < this->courseDB.size()) {
		return false;
	}

	if (userId < this->studentDB.size()) {
		return false;
	}

	for (UINT index = 0; index < this->courseDB[courseId].studentList.size(); index++) {
		if ()
	}


}