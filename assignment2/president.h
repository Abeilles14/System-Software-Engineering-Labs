#pragma once

#include "user.h"

using namespace std;

class President : public User {

public:
	President();
	President(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength);

	// Helpers
	void Reset();

};