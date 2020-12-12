#pragma once

#include "user.h"
#include "student.h"

using namespace std;

class President : public User {
private:
	vector<Student*> suspendedList;
public:
	President();
	President(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength);

	// Accessors
	void DisplaySuspended() const;

	// Mutators
	bool AddSuspended(Student* student);
	bool RemoveSuspended(UINT studentId);

	// Helpers
	void Reset();

};