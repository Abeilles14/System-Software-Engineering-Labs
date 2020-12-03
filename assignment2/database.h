#pragma once

#include "constants.h"
#include "student.h"
#include "professor.h"
#include "admin.h"
#include "president.h"
#include "user.h"
#include "course.h"

using namespace std;

class SystemDatabase {
private:
	vector<User*> userDB;
	vector<Course*> courseDB;

public:
	SystemDatabase();

	// Accessors
	bool GetUser(const char* cwlUsername, UINT usernameLength, const char* cwlPassword, UINT passwordLength, User* &accessingUser);
	void GetCourseDatabase();
	void GetStudentDatabase();
	void GetProfessorDatabase();
	Course* GetCoursePtr(UINT courseId);
	User* GetUserPtr(UINT userId);

	// Mutators
	bool CreateUser(UINT userId, UINT userType, char* name, UINT nameLength, char* userName, UINT usernameLength, char* password, UINT passwordLength);
	bool RemoveUser(UINT userId);

	bool CreateCourse(UINT courseId, char* courseName, UINT courseNameLength);
	bool RemoveCourse(UINT courseId);

	// Helpers
	void Reset();

};