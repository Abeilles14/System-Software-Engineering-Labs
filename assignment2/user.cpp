#include "user.h"

User::User() {
	this->Reset();
}

User::User(UINT userId, char* name, UINT nameLength, UINT userType, char* userName, UINT usernameLength, char* password, UINT passwordLength) {
	this->Reset();
	this->InitializeUser(userId, name, nameLength, userType, userName, usernameLength, password, passwordLength);
}

// Accessors
UINT User::GetUserId() const {
	return this->userId;
}
const char* User::GetName() const {
	return this->name;
}

UINT User::GetUserType() const {
	return this->userType;
}
const char* User::GetCwlUsername() const {
	return this->cwlUsername;
}

const char* User::GetCwlPassword() const {
	return this->cwlPassword;
}

// Mutators
bool User::SetUserId(UINT userId) {
	this->userId = userId;
	return true;
}
bool User::SetName(char* name, UINT nameLength) {
	memcpy(this->name, name, nameLength);
	return true;
}
bool User::SetUserType(UINT userType) {
	this->userType = userType;
	return true;
}
bool User::SetUserName(char* userName, UINT usernameLength) {
	memcpy(this->cwlUsername, userName, usernameLength);
	return true;
}
bool User::SetPassword(char* password, UINT passwordLength) {
	memcpy(this->cwlPassword, password, passwordLength);
	return true;
}

// Helpers
void User::Reset() {
	this->userId = 0;
	memset(name, 0, 20);
	this->userType = 0;
	memset(cwlUsername, 0, 20);
	memset(cwlPassword, 0, 20);
}

void User::InitializeUser(UINT userId, char* name, UINT nameLength, UINT userType, char* userName, UINT usernameLength, char* password, UINT passwordLength) {
	SetUserId(userId);
	SetName(name, nameLength);
	SetUserType(userType);
	SetUserName(userName, usernameLength);
	SetPassword(password, passwordLength);
}