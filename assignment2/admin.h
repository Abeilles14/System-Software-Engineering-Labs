#pragma once

#include "user.h"

using namespace std;

class Admin : public User {
public:
	Admin();
	Admin(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength);

	// Helpers
	void Reset();

};