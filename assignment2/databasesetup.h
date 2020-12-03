#pragma once

#include "database.h"

struct courseSetup {
	UINT courseNumber;
	char courseName[20];
};

courseSetup courseInitialization[5]{
	{CPEN211, "CPEN 211"},
	{CPEN333, "CPEN 333"},
	{CPEN412, "CPEN 412"},
	{CPEN391, "CPEN 391"},
	{MATH256, "MATH 256"}
};

struct specializationSetup {
	UINT specializationNumber;
	char specializationName[20];
	vector<courseBase> enrolledCourses;
	UINT averageGrade;
};

specializationSetup specInitialization[5]{
	{CPEN, "CPEN", {{CPEN211, "CPEN 211"}, {CPEN333, "CPEN 333"}}, 85},
	{ELEC, "ELEC", {{CPEN211, "CPEN 211"}}, 75},
	{ENGPHYS, "ENGPHYS", {{MATH256, "MATH 256"}}, 80},
	{MECH, "MECH", {{MATH256, "MATH 256"}, {CPEN333, "CPEN 333"}}, 75},
	{IGEN, "IGEN", {{MATH256, "MATH 256"}}, 60}
};

struct userSetup {
	UINT userId;
	char name[20];
	char userName[20];
	char password[20];
};

userSetup studentInitialization[5] {
	{12345678, "Justin Chang", "user1", "password1"},
	{22345678, "Isabelle Andre", "user2", "password2"},
	{32345678, "Nestor Brito", "user3", "password3"},
	{42345678, "Debby Lin", "user4", "password4"},
	{52345678, "Matthew Sam", "user5", "password5"}
};

userSetup profInitialization [5] {
	{62345678, "Paul Davie", "prof1", "password1"},
	{72345678, "Tor Aamodt", "prof2", "password2"},
	{82345678, "bytttt", "prof3", "password3"},
	{92345678, "Tor asdfasd", "prof4", "password4"},
	{12345679, "Tor as", "prof5", "password5"}
};


SystemDatabase databaseSetup() {
	SystemDatabase database;

	// Initialize courses and students
	for (UINT index = 0; index < 5; index++) {
		database.CreateUser(studentInitialization[index].userId, userTypes::typeStudent,studentInitialization[index].name, strlen(studentInitialization[index].name),
			studentInitialization[index].userName, strlen(studentInitialization[index].userName),
			studentInitialization[index].password, strlen(studentInitialization[index].password));

		database.CreateCourse(courseInitialization[index].courseNumber, courseInitialization[index].courseName,
			strlen(courseInitialization[index].courseName));

		database.CreateSpecialization(specInitialization[index].specializationNumber, specInitialization[index].specializationName,
			strlen(specInitialization[index].specializationName),
			specInitialization[index].averageGrade);

		database.CreateUser(profInitialization[index].userId, userTypes::typeProfessor, profInitialization[index].name, strlen(profInitialization[index].name),
			profInitialization[index].userName, strlen(profInitialization[index].userName),
			profInitialization[index].password, strlen(profInitialization[index].password));
	}

	// Specifics

	// Prereq of cpen211 for cpen 412
	Course* coursePtr = database.GetCoursePtr(CPEN412);
	coursePtr->SetPrereqCourseId(CPEN211);

	grade cpen211Grade = { CPEN211, "CPEN 211", 100 };

	Student* studentPtr = (Student*)database.GetUserPtr(12345678);
	studentPtr->AddGrade(cpen211Grade);

	// Specialization Requirements
	Specialization* cpenPtr = database.GetSpecializationPtr(CPEN);
	cpenPtr->AddEnrolledCourse({ CPEN211, "CPEN 211" });
	cpenPtr->AddEnrolledCourse({ CPEN333, "CPEN 333" });

	Specialization* elecPtr = database.GetSpecializationPtr(ELEC);
	elecPtr->AddEnrolledCourse({ CPEN211, "CPEN 211" });

	Specialization* engphysPtr = database.GetSpecializationPtr(ENGPHYS);
	engphysPtr->AddEnrolledCourse({ MATH256, "MATH 256" });

	Specialization* mechPtr = database.GetSpecializationPtr(MECH);
	mechPtr->AddEnrolledCourse({ MATH256, "MATH 256" });
	mechPtr->AddEnrolledCourse({ CPEN333, "CPEN 333" });

	Specialization* igenPtr = database.GetSpecializationPtr(IGEN);
	igenPtr->AddEnrolledCourse({ MATH256, "MATH 256" });

	// Add administrator and President

	// Create president
	char presidentName[] = "Santa Ono";
	char adminName[] = "James Olson";
	char presidentUser[] = "president";
	char adminUser[] = "admin";
	char adminPassword[] = "password";

	database.CreateUser(99999999, userTypes::typePresident, presidentName, 10, presidentUser, 10, adminPassword, 9);

	// Create admin
	database.CreateUser(88888888, userTypes::typeAdmin, adminName, 12, adminUser, 10, adminPassword, 9);

	return database;

}