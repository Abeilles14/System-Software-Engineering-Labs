#include "admin.h"
#include "student.h"
#include "specialization.h"
#include <vector>
#include <numeric>

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
		cout << this->requestList[index].studentNumber << ": " << this->requestList[index].studentName << ": " << this->requestList[index].specializationName << endl;
	}
}

UINT Admin::GetRequestSpecializationNumber(UINT userId) const {
	for (UINT index = 0; index < this->requestList.size(); index++) {
		if (this->requestList[index].studentNumber == userId) {
			return this->requestList[index].specializationId;
		}
	}

	return NULL;
}

// Mutators
bool checkRequirements(Student* thisStudent, Specialization* specialization) {
	int studentGrade = accumulate(thisStudent->GetGradesList()->begin(), thisStudent->GetGradesList()->end(), 0);

	// check student average
	if (studentGrade >= specialization->GetAverageGrade()) {

		// check student enrolled classes
		for (UINT index = 0; index < thisStudent->GetEnrolledCoursesList()->size(); index++) {
			if (std::find(thisStudent->GetEnrolledCoursesList()->begin(), thisStudent->GetEnrolledCoursesList()->end(), specialization->GetEnrolledCourses()[index]) == specialization->GetEnrolledCourses()->end()) {
				cout << "Student Does Not Meet Requirements to Enter Specialization\n";
				return false;
			}
		}
		cout << "Student Meets Requirements to Enter Specialization\n";
		return true;
	}

	cout << "Student Does Not Meet Requirements to Enter Specialization\n";
	return false;
}

bool Admin::ApproveRequest(Student* student) {
	for (UINT index = 0; index < this->requestList.size(); index++) {
		if (this->requestList[index].studentNumber == student->GetUserId()) {
			student->SetSpecialization(this->requestList[index].specializationName, sizeof(this->requestList[index].specializationName));
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