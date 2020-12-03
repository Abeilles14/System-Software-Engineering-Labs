#include "admin.h"

Admin::Admin() {
	this->Reset();
}
Admin::Admin(UINT userId, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength) {
	this->Reset();

	this->InitializeUser(userId, name, nameLength, userTypes::typeAdmin, userName, usernameLength, password, passwordLength);
}

// Helpers
void Admin::Reset() {
	User::Reset();
}