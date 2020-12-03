#include "president.h"

President::President() {
	this->Reset();
}
President::President(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength) {
	this->Reset();

	this->InitializeUser(userId, name, nameLength, userTypes::typePresident, userName, usernameLength, password, passwordLength);
}

// Accessors
void President::DisplaySuspended() const {
	for (UINT index = 0; index < this->suspendedList.size(); index++) {
		cout << this->suspendedList[index]->GetUserId() << ": " << this->suspendedList[index]->GetName() << endl;
	}
}

// Mutators
bool President::AddSuspended(Student* student) {
	this->suspendedList.push_back(student);		//TODO: fix bug
	return true;
}

bool President::RemoveSuspended(UINT studentId) {
	for (UINT index = 0; index < this->suspendedList.size(); index++) {
		if (this->suspendedList[index]->GetUserId() == studentId) {
			this->suspendedList.erase(this->suspendedList.begin() + index);
			return true;
		}
	}
	return false;
}

// Helpers
void President::Reset() {
	User::Reset();
}