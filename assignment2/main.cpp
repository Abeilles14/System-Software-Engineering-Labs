#include "stdio.h"
#include "constants.h"
#include "databasesetup.h"
#include <string.h>

using namespace std;

int main() {
	UINT userInput;

	UINT userType;
	string username;
	string password;

	string newAssignment;

	UINT studentNumber;
	char studentName[20];
	char studentUsername[20];
	char studentPassword[20];
	char request[20];

	// Database and accessing user
	SystemDatabase universityDatabase = databaseSetup();
	User* accessingUser = NULL;

	// User and database pointers for modifying values
	User* userPtr = NULL;
	Course* coursePtr = NULL;

	bool loggedIn = false;

	
	for (;;) {

		// CWL LOGIN'
		while (!loggedIn) {
			cout << "\nCWL LOGIN\n \
					Please enter your CWL Login Username: ";
			cin >> username;
			cout << "Please enter your CWL Login Password: ";
			cin >> password;

			loggedIn = universityDatabase.GetUser(username.c_str(), username.length(), password.c_str(), password.length(), accessingUser);
		}
		cout << "Logged in. Welcome " << accessingUser->GetName() << endl << endl;

		while (loggedIn) {

			cout << "\nMAIN MENU OPTIONS\n"
				"0 : Logout\n"
				"1 : Access Course Database and Options\n"
				"2 : Access Student Database and Options\n" << endl;

			cin >> userInput;

			switch (userInput) {
				case 0:		// LOGOUT
					cout << "Logging out...\n";
					loggedIn = false;

					break;

				case 1: {		// COURSE DATABASE
					Professor* professorPtr = NULL;
					cout << "Accessing Course Database\n";

					//display all course list
					universityDatabase.GetCourseDatabase();

					cout << "\nCOURSE MENU OPTIONS\n";

					switch (accessingUser->GetUserType()) {

					case typePresident: {
						cout << "1 : Get Course Information\n"
							"2 : Back To Main Menu\n" << endl;
						cin >> userInput;

						switch (userInput) {
						case 1:
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							// display course Information
							cout << "Displaying Course " << userInput << "Information";
							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							coursePtr->DisplayCourseInfo();

							break;
						default:
							// do nothing, back to main menu
							break;
						}
						break;
					}
					case typeAdmin: {
						cout << "1 : Get Gourse Information\n"
							"2 : Assign Professor To Course\n"
							"3 : Remove Professor From Course\n"
							"4 : Back To Main Menu\n" << endl;
						cin >> userInput;

						switch (userInput) {
						case 1: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							// display course Information
							cout << "Displaying Course " << userInput << "Information";
							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							coursePtr->DisplayCourseInfo();

							break;
						}
						case 2: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;
							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							// display list of professors
							universityDatabase.GetProfessorDatabase();

							cout << "Enter Professor ID From Professor List: ";
							cin >> userInput;

							// update prof to assign course to prof
							userPtr = universityDatabase.GetUserPtr(userInput);
							if (userPtr == NULL) {
								break;
							}
							professorPtr = (Professor*)userPtr;
							professorPtr->AddCourse(coursePtr);		//TODO: fix bug
							cout << "Professor Added to Course";

							break;
						}
						case 3: {
							// display list of professors
							universityDatabase.GetProfessorDatabase();

							cout << "Enter Professor ID From Professor List: ";
							cin >> userInput;

							// update prof to assign course to prof
							userPtr = universityDatabase.GetUserPtr(userInput);
							if (userPtr == NULL) {
								break;
							}
							professorPtr = (Professor*)userPtr;

							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							// update prof to unassign course to prof
							professorPtr->RemoveCourse(userInput);		//TODO: fix bug
							cout << "Professor Unassigned To Course";
						
							break;
						}
						default:
							// do nothing, back to main menu
							break;
						}
						break;
					}

					case typeProfessor: {
						cout << "1 : Get Gourse Information\n"
							"2 : View Course Assessments\n"
							"3 : Create Assessment Proposal\n"
							"4 : Delete Assessment Proposal\n"
							"5 : Back To Main Menu\n" << endl;
						cin >> userInput;

						switch (userInput) {
						case 1: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							// display course Information
							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							coursePtr->DisplayCourseInfo();
							cout << "Displaying Course " << userInput << " Information";

							break;
						}
						case 2: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							// display list course assessments
							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							cout << "Displaying Course " << userInput << " Assignments";
							coursePtr->DisplayAssignments();

							break;
						}
						case 3: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							cout << "Enter Assignment Name and/or Description: ";
							cin >> newAssignment;

							// add assignment to course assignment list
							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							coursePtr->AddAssignment(newAssignment);
							cout << "Assignment " << newAssignment << " Created";

							break;
						}
						case 4: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							// display list course assessments
							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							coursePtr->DisplayAssignments();

							cout << "Enter Assignment Name From Assignments List: ";
							cin >> newAssignment;

							// remove assignment from course assignment list
							coursePtr->RemoveAssignment(newAssignment);
							cout << "Assignment " << newAssignment << " Deleted";

							break;
						}
						default:
							// do nothing, back to main menu
							break;
						}
						break;
					}

					case typeStudent: {
						// For use with student functions
						Student* studentPtr = (Student*)accessingUser;

						cout << "1 : Get Gourse Information\n"
							"2 : Enroll In Course\n"
							"3 : Drop Course\n"
							"4 : View Course Assessments\n"
							"5 : Back To Main Menu\n" << endl;
						cin >> userInput;

						switch (userInput) {
						case 1: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							cout << "Displaying Course " << userInput << " Information";
							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							coursePtr->DisplayCourseInfo();

							break;
						}
						case 2: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							if (!coursePtr->AddStudent(studentPtr)) {
								cout << "Student does not meet pre-requisites for course" << endl;
								break;
							}
							studentPtr->AddCourse(coursePtr->GetCourseNumber(), coursePtr->GetCourseName(), strlen(coursePtr->GetCourseName()));
							cout << "Student enrolled in course: " << coursePtr->GetCourseName() << endl;

							break;
						}
						case 3: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}

							if (!coursePtr->RemoveStudent(studentPtr->GetUserId())) {
								cout << "User is not enrolled in course";
								break;
							}

							studentPtr->RemoveCourse(userInput);
							cout << "Student removed from course " << coursePtr->GetCourseName() << endl;

							break;
						}
						case 4: {
							cout << "Enter Course ID From Course List: ";
							cin >> userInput;

							// display course assigments
							cout << "Displaying Course " << userInput << " Information";
							coursePtr = universityDatabase.GetCoursePtr(userInput);
							if (coursePtr == NULL) {
								break;
							}
							coursePtr->DisplayAssignments();

							break;
						}
						default:
							// do nothing, back to main menu
							break;
						}

						break;
					}
					default:
						cout << "Error in System Database\n";
						break;
					}

					break;
				}

				case 2: {		// STUDENT DATABASE
					cout << "Accessing User Database\n";
					cout << "\nSTUDENT MENU OPTIONS\n";

					Student* studentPtr = NULL;
					President* presidentPtr = NULL;

					Admin* adminPtr = (Admin*)universityDatabase.GetUserPtr(88888888);		// using a constant single faculty admin for this system

					switch (accessingUser->GetUserType()) {
						case typePresident: {		// dean and president have same course database privileges
							cout << "1 : Get Student Information\n"
									"2 : Display Suspended Students\n"
									"3 : Suspend Student\n"
									"4 : Unsuspend Student\n"
									"5 : Back To Main Menu\n" << endl;

							presidentPtr = (President*)accessingUser;

							// display student list
							universityDatabase.GetStudentDatabase();
							cin >> userInput;

							switch (userInput) {
							case 1: {
								cout << "Enter Student ID From Student List: ";
								cin >> userInput;

								// display student information
								userPtr = universityDatabase.GetUserPtr(userInput);
								if (userPtr == NULL) {
									break;
								}
								studentPtr = (Student*)userPtr;
								studentPtr->DisplayStudentInfo();

								break;
							}
							case 2: {
								cout << "Displaying Suspended Students: \n";
								presidentPtr->DisplaySuspended();

								break;
							}
							case 3: {
								cout << "Enter Student ID From Student List: ";
								cin >> userInput;

								// suspend student
								userPtr = universityDatabase.GetUserPtr(userInput);
								if (userPtr == NULL) {
									break;
								}
								studentPtr = (Student*)userPtr;
								presidentPtr->AddSuspended(studentPtr);
								cout << "Student " << userInput << " Suspended";

								break;
							}
							case 4: {
								cout << "Enter Student ID From Student List: ";
								cin >> userInput;

								// unsuspend student
								presidentPtr->RemoveSuspended(userInput);
								cout << "Student " << userInput << " Unsuspended";

								break;
								}
							default:
								// do nothing, back to main menu
								break;
							}
							break;
						}

						case typeAdmin: {
							cout << "1 : Get Student Information\n"
									"2 : Get Student Requests\n"
									"3 : Create Student\n"
									"4 : Delete Student\n"
									"5 : Back To Main Menu\n" << endl;

							adminPtr = (Admin*)accessingUser;

							// display student list
							universityDatabase.GetStudentDatabase();
							cin >> userInput;

							switch (userInput) {
								case 1: {
									cout << "Enter Student ID From Student List: ";
									cin >> userInput;

									// display student information
									userPtr = universityDatabase.GetUserPtr(userInput);
									if (userPtr == NULL) {
										break;
									}
									studentPtr = (Student*)userPtr;
									studentPtr->DisplayStudentInfo();

									break;
								}
								case 2:
									cout << "Enter Student ID From Student List: ";
									cin >> userInput;

									// display requests from student
									adminPtr->DisplayStudentRequests();

									cout << "\nMENU OPTIONS\n"
											"1 : Approve Student Request\n"
											"2 : Deny Student Request\n";

									cin >> userInput;

									switch (userInput) {
									case 1:
										cout << "Enter Student ID From Request List: ";
										cin >> userInput;

										userPtr = universityDatabase.GetUserPtr(userInput);
										if (userPtr == NULL) {
											break;
										}
										studentPtr = (Student*)userPtr;

										// approve student request
										adminPtr->ApproveRequest(studentPtr);

										break;
									case 2:
										cout << "Enter Student ID From Request List: ";
										cin >> userInput;

										// deny student request
										adminPtr->DenyRequest(userInput);

										break;
									}

									break;
								case 3: {
									cout << "Enter New Student ID: ";
									cin >> studentNumber;
									cout << "Enter New Student Name: ";
									cin >> studentName;
									cout << "Enter New Student User Name: ";
									cin >> studentUsername;
									cout << "Enter New Student Password: ";
									cin >> studentPassword;

									// create new user
									universityDatabase.CreateUser(studentNumber, typeStudent, studentName, sizeof(studentName), studentUsername, sizeof(studentUsername), studentPassword, sizeof(studentPassword));
									cout << "New Student Enrolled (Created)\n";

									break;
								}
								case 4: {
									cout << "Enter Student ID From Student List: ";
									cin >> userInput;

									//TODO: delete student
									universityDatabase.RemoveUser(userInput);
									cout << "Student Graduated (Removed)\n";

									break;
								}
								default:
									// do nothing, back to main menu
									break;
								}
							break;
						}

						case typeProfessor: {
							cout << "1 : Get Student Information\n"
								"2 : Back To Main Menu\n" << endl;

							//display all students
							universityDatabase.GetStudentDatabase();

							cin >> userInput;

							switch (userInput) {
							case 1: {
								cout << "Enter Student ID From Student List: ";
								cin >> userInput;

								// display student information
								cout << "Displaying Student Info";
								userPtr = universityDatabase.GetUserPtr(userInput);
								if (userPtr == NULL) {
									break;
								}
								studentPtr = (Student*)userPtr;
								studentPtr->DisplayStudentInfo();

								break;
							}
							default:
								// do nothing, back to main menu
								break;
							}

							break;
						}
						case typeStudent: {
							cout << "1 : Get Student User Information\n"
								"2 : Create Specialization Request\n" << endl;

							cin >> userInput;

							switch (userInput) {
								case 1: {
									// display student information
									cout << "Displaying Student User Info";

									studentPtr = (Student*)accessingUser;
									studentPtr->DisplayStudentInfo();

									break;
								}
								case 2: {
									// create request to admin
									cout << "Enter Specialization Name: ";
									cin >> request;

									studentPtr->CreateRequest(adminPtr, studentPtr->GetUserId(), studentPtr->GetName(), request);
								}
							}

							break;
						}
						default:
							cout << "Unrecognized command, please refer to commands menu";

							break;
					}
				
					break;
				}	
			}
		}
	}
	return 0;
}