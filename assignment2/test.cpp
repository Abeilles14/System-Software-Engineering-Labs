#include "pch.h"
#include "../databasesetup.h"
#include "../constants.h"



// Student Requests admittance to CPEN
TEST(UniversityTests, StudentAdmittanceToSecondYear) {
	UINT studentNumber = 12345678;


	SystemDatabase exampleDatabase = databaseSetup();

	// Get student ptr
	Student* studentPtr = (Student*)exampleDatabase.GetUserPtr(studentNumber);		// Get faculty admin pointer

	// Get admin ptr
	Admin* adminPtr = (Admin*)exampleDatabase.GetUserPtr(88888888);		// Get faculty admin pointer

	// To CPEN
	Specialization* specializationPtr = exampleDatabase.GetSpecializationPtr(CPEN);

	ASSERT_TRUE(adminPtr != NULL);
	ASSERT_TRUE(specializationPtr != NULL);
	ASSERT_TRUE(studentPtr != NULL);

	ASSERT_TRUE(studentPtr->CreateRequest(adminPtr, studentPtr->GetUserId(), studentPtr->GetName(), sizeof(studentPtr->GetName()), 
		CPEN211, specializationPtr->GetSpecializationName(), sizeof(specializationPtr->GetSpecializationName())));

	// Check that the request exists with the admin
	ASSERT_EQ(adminPtr->GetRequestSpecializationNumber(studentNumber), CPEN211);
}