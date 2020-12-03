#include "president.h"

President::President() {
	this->Reset();
}
President::President(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength) {
	this->Reset();

	this->InitializeUser(userId, name, nameLength, userTypes::typePresident, userName, usernameLength, password, passwordLength);
}

// Helpers
void President::Reset() {
	User::Reset();
}