#pragma once

#include "constants.h"

class User {
private:
	UINT userId;
	char name[20];
	UINT userType;
	char cwlUsername[20];
	char cwlPassword[20];

public:
	User();
	User(UINT userId, char* name, UINT nameLength, UINT userType, char* userName, UINT usernameLength, char* password, UINT passwordLength);

	// Accessors
	UINT GetUserId() const;
	const char* GetName() const;
	UINT GetUserType() const;
	const char* GetCwlUsername() const;
	const char* GetCwlPassword() const;

	// Mutators
	void InitializeUser(UINT userId, char* name, UINT nameLength, UINT userType, char* userName, UINT usernameLength, char* password, UINT passwordLength);
	bool SetUserId(UINT userId);
	bool SetName(char* name, UINT nameLength);
	bool SetUserType(UINT userType);
	bool SetUserName(char* userName, UINT usernameLength);
	bool SetPassword(char* password, UINT passwordLength);

	// Helpers
	void Reset();

};