#include "database.h"

SystemDatabase::SystemDatabase() {
	this->Reset();
}

void SystemDatabase::Reset() {
	this->userDB.clear();
	this->courseDB.clear();
}

bool SystemDatabase::GetUser(const char* cwlUsername, UINT usernameLength, const char* cwlPassword, UINT passwordLength, User* &accessingUser) {
	UINT userSize = this->userDB.size();
	for (UINT index = 0; index < userSize; index++) {
		if (usernameLength != strlen(this->userDB[index]->GetCwlUsername())) {
			continue;
		}

		if (memcmp(cwlUsername, this->userDB[index]->GetCwlUsername(), usernameLength) != 0) {
			continue;
		}

		if (passwordLength != strlen(this->userDB[index]->GetCwlPassword())) {
			cout << "Incorrect password\n";
			continue;
		}

		if (memcmp(cwlPassword, this->userDB[index]->GetCwlPassword(), passwordLength) != 0) {
			cout << "Incorrect password\n";
			break;
		}
		// User has been found
		accessingUser = this->userDB[index];

		return true;
	}
	cout << "Unable to login\n";
	return false;
}

// Display course list
void SystemDatabase::GetCourseDatabase() {
	UINT courseSize = this->courseDB.size();
	for (UINT index = 0; index < courseSize; index++) {
		this->courseDB[index]->DisplayCourseInfo();
	}
}

// Display student list
void SystemDatabase::GetStudentDatabase() {
	UINT userSize = this->userDB.size();
	for (UINT index = 0; index < userSize; index++) {
		if (this->userDB[index]->GetUserType() == userTypes::typeStudent) {
			cout << this->userDB[index]->GetUserId() << ": " << this->userDB[index]->GetName() << endl;
		}
	}
}

// Display professor list
void SystemDatabase::GetProfessorDatabase() {
	UINT userSize = this->userDB.size();
	for (UINT index = 0; index < userSize; index++) {
		if (this->userDB[index]->GetUserType() == userTypes::typeProfessor) {
			cout << this->userDB[index]->GetUserId() << ": " << this->userDB[index]->GetName() << endl;
		}
	}
}

Course* SystemDatabase::GetCoursePtr(UINT courseId) {
	// Package course info
	for (UINT index = 0; index < this->courseDB.size(); index++) {
		if (courseDB[index]->GetCourseNumber() == courseId) {
			return this->courseDB[index];
		}
	}
	cout << "Course ID not found";
	return NULL;
}

User* SystemDatabase::GetUserPtr(UINT userId) {
	for (UINT index = 0; index < this->userDB.size(); index++) {
		if (userDB[index]->GetUserId() == userId) {
			return this->userDB[index];
		}
	}
	cout << "User id not found";
	return NULL;
}

void GetStudentRequests();

// Mutators
bool SystemDatabase::CreateUser(UINT userId, UINT userType, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength) {
	switch (userType) {
		case userTypes::typeStudent:
			this->userDB.push_back(new Student(userId, name, nameLength, userName, usernameLength, password, passwordLength));
			break;

		case userTypes::typeProfessor:
			this->userDB.push_back(new Professor(userId, name, nameLength, userName, usernameLength, password, passwordLength));
			break;

		case userTypes::typeAdmin:
			this->userDB.push_back(new Admin(userId, name, nameLength, userName, usernameLength, password, passwordLength));
			break;

		case userTypes::typePresident:
			this->userDB.push_back(new President(userId, name, nameLength, userName, usernameLength, password, passwordLength));
			break;

		default:
			cout << "Error: Unknown user type" << endl;
			return false;
	}
	return true;
}

bool SystemDatabase::RemoveUser(UINT userId) {
	for (UINT index = 0; index < this->userDB.size(); index++) {
		if (userDB[index]->GetUserId() == userId) {
			delete this->userDB[index];
			this->userDB.erase(this->userDB.begin() + index);
			return true;
		}
	}
	return false;
}

bool SystemDatabase::CreateCourse(UINT courseId, char* courseName, UINT courseNameLength) {
	this->courseDB.push_back(new Course(courseId, courseName, courseNameLength));
	return true;
}

bool SystemDatabase::RemoveCourse(UINT courseId) {
	for (UINT index = 0; index < this->courseDB.size(); index++) {
		if (courseDB[index]->GetCourseNumber() == courseId) {
			delete this->courseDB[index];
			this->courseDB.erase(this->courseDB.begin() + index);
			return true;
		}
	}
	return false;
}