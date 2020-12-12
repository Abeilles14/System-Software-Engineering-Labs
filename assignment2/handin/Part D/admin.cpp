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
bool Admin::CheckRequirements(Student* thisStudent, Specialization* specialization) {
	UINT studentGrade = 0; 

	// Calculate student avg
	for (UINT index = 0; index < thisStudent->GetGradesList()->size(); index++) {
		studentGrade += thisStudent->GetGradesList()->at(index).grade;
	}
	studentGrade = thisStudent->GetGradesList()->size();

	// check student average
	bool found = false;

	if (studentGrade >= specialization->GetAverageGrade()) {

		// check student enrolled classes
		for (UINT index = 0; index < specialization->GetEnrolledCourses()->size(); index++) {
			found = false;
			for (UINT index2 = 0; index2 < thisStudent->GetEnrolledCoursesList()->size(); index2++) {
				// Check if student has the course in its list. if it does, break the loop and continue.
				if (specialization->GetEnrolledCourses()->at(index).courseNumber == thisStudent->GetEnrolledCoursesList()->at(index2).courseNumber) {
					found = true;
					break;
				}
			}
			if (!found) {
				// Was not able to find the indicated course
				return false;
			}
		}
		return true;
	}
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