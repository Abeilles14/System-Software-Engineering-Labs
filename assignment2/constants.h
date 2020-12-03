#pragma once


#include <vector>
#include <string>
#include <iostream>
#include <cstring>

#define UINT unsigned int


enum userTypes {
	typePresident,
	typeAdmin,
	typeProfessor,
	typeStudent
};

enum courseIdList {
	CPEN211,
	CPEN333,
	CPEN412,
	CPEN391,
	MATH256,
	NONE
};

struct courseBase {
	UINT courseNumber;
	char courseName[20];
};

struct grade {
	UINT courseNumber;
	char courseName[9];
	UINT grade;
};

struct studentRequest {
	UINT studentNumber;
	char studentName[20];
	char specialization[20];
};

/*
struct grades {
	char courseId[9];
	UINT grade;
};

struct course {
	
};


struct student {
	UINT studentId;
	char name[20];
	char specialization[20] = "none";
	vector<grades> gradesList;
	vector<string> courseList;
};

vector<course> initialCourseList = { 
	{CPEN211, "CPEN 211"},
	{CPEN333, "CPEN 333"},
	{CPEN391, "CPEN 391"},
	{CPEN412, "CPEN 412"},
	{MATH256, "ELEC 342"}
}
*/