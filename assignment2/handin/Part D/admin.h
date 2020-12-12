#pragma once

#include "user.h"

class Student;
class Specialization;

using namespace std;

class Admin : public User {
private:

public:
	vector<studentRequest> requestList;

	Admin();
	Admin(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength);
	
	// Accessors
	void DisplayStudentRequests() const;
	UINT GetRequestSpecializationNumber(UINT userId) const;

	// Mutators
	bool CheckRequirements(Student* thisStudent, Specialization* specialization);
	bool ApproveRequest(Student* student);
	bool DenyRequest(UINT userId);

	// Helpers
	void Reset();

};