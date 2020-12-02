#pragma once

#include "constants.h"

using namespace std;

class SystemDatabase {
private:
	vector<student> studentDB;
	vector<course> courseDB;
	vector<user> userDB;

public:
	SystemDatabase();
	SystemDatabase(vector<student> studentList, vector<course> courseList);
	~SystemDatabase();

	// Accessors
	bool GetUser(char* cwlUsername, UINT usernameLength, char* cwlPassword, UINT passwordLength, UINT userId, UINT userType);
	void GetCourseDatabase();
	void GetStudentDatabase();
	void GetCourseInfo(UINT courseId);
	void GetStudentInfo(UINT userId);
	void GetStudentRequests();

	// Mutators
	bool EnrollInCourse(UINT userId, UINT courseId);
	bool DropCourse(UINT userId, UINT courseId);
	bool AssignToCourse(UINT userId, UINT courseId);
	bool RemoveFromCourse(UINT userId, UINT courseId);

	bool SuspendStduent(UINT userId);
	bool UnSuspendStudent(UINT userId);
	bool ApproveStudentRequest(UINT requestNumber);
	bool DenyStudentRequest(UINT requestNumber);
	
	bool CreateAssessmentProposal(string assignment, UINT courseId);
	bool RemoveAssessment(UINT assignmentNumber, UINT courseId);
	bool SelectSpecialization(UINT userId, UINT specializationSelection);

	bool CreateStudent(UINT userId, char* studentName);
	bool RemoveStudent(UINT userId);

	// Helpers
	void Reset();

};