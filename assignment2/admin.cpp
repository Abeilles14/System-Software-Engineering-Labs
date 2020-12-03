#include "admin.h"
#include "student.h"

Admin::Admin() {
	this->Reset();
}
Admin::Admin(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength) {
	this->Reset();

	this->InitializeUser(userId, name, nameLength, userTypes::typeAdmin, userName, usernameLength, password, passwordLength);
}

// Accessors
void Admin::DisplayStudentRequests() const {
	for (UINT index = 0; index < this->requestList.size(); index++) {
		cout << this->requestList[index].studentNumber << ": " << this->requestList[index].studentName << ": " << this->requestList[index].specialization << endl;
	}
}

// Mutators
bool Admin::ApproveRequest(Student* student) {
	for (UINT index = 0; index < this->requestList.size(); index++) {
		if (this->requestList[index].studentNumber == student->GetUserId()) {
			student->SetSpecialization(this->requestList[index].specialization, sizeof(this->requestList[index].specialization));
			this->requestList.erase(this->requestList.begin() + index);
			cout << "Student " << student->GetUserId() << " Request Approved";

			return true;
		}
	}

	return false;
}

bool Admin::DenyRequest(UINT userId) {
	for (UINT index = 0; index < this->requestList.size(); index++) {
		if (this->requestList[index].studentNumber == userId) {
			this->requestList.erase(this->requestList.begin() + index);
			cout << "Student " << userId << " Request Denied";

			return true;
		}
	}

	return false;
}

// Helpers
void Admin::Reset() {
	User::Reset();
}