#include "..\..\rt.h"

struct example{
	int x;
	float y;
};

int i = 5;
int array1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

char name[15] = "Hello World";
struct example mystruct = { 2, 5.5 };

int main() {
	cout << "Parent Process Creating the Pipelines\n";

	CPipe pipe1("MyPipe1", 1024);		// create pipes size 1024
	CPipe pipe2("MyPipe2", 1024);

	cout << "Parent Process Creating Child Processes to Read from Pipelines\n";

	CProcess p1("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab4\\lab4\\Debug\\Child1.exe", 	// create child process
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	CProcess p2("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab4\\lab4\\Debug\\Child2.exe", 	// create child process
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	cout << "Hit RETURN to Write the integer " << i << " to the pipelines\n";
	getchar();

	pipe1.Write(&i, sizeof(i));						// write the int 'i' to the pipe
	pipe2.Write(&i, sizeof(i));

	cout << "Hit RETURN to Write the integer array 1 2 3 4 5 6 7 8 9 0 to the pipeline\n";
	getchar();

	pipe1.Write(&array1[0], sizeof(array1));			// write the array of integers' to the pipe
	pipe2.Write(&array1[0], sizeof(array1));

	cout << "Hit RETURN to Write the string " << name << " to the pipeline\n";
	getchar();

	pipe1.Write(&name[0], sizeof(name));				// write the string to the pipe
	pipe2.Write(&name[0], sizeof(name));

	cout << "Hit RETURN to Write the structure [" << mystruct.x << ", " << mystruct.y << "] to the pipeline\n";
	getchar();

	pipe1.Write(&mystruct, sizeof(mystruct));			// write the structure to the pipeline
	pipe2.Write(&mystruct, sizeof(mystruct));

	p1.WaitForProcess();

	return 0;			

}