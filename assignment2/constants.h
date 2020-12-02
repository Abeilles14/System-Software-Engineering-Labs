#pragma once


#include <vector>
#include <string>
#include <iostream>

#define UINT unsigned int

using namespace std;

enum userType {
	typepPresident,
	typeDean,
	typeAdmin,
	typeProfessor,
	typeStudent
};

enum listOfCourses {
	ELEC342,
	ELEC315,
	CPEN211,
	CPEN333,
	CPEN412,
	CPEN391,
	MATH256
};


struct grades {
	char courseId[9];
	UINT grade;
};

struct course {
	UINT courseNumber;
	char courseName[9];
	vector<UINT>studentList;
	vector<string>assignments;
};


struct student {
	UINT studentId;
	char name[20];
	char specialization[20] = "none";
	vector<grades> gradesList;
	vector<string> courseList;
};

struct user {
	char cwlUsername[20];
	char cwlPassword[20];
	UINT userId;
	UINT userType;
};

vector<course> initialCourseList = { 
	{CPEN211, "CPEN 211"},
	{CPEN333, "CPEN 333"},
	{CPEN391, "CPEN 391"},
	{CPEN412, "CPEN 412"},
	{MATH256, "ELEC 342"}
}