#include <iostream>
#include "../rt.h"

using namespace std;

int main() {
	cout << "Creating 3 Child Processes\n";

	CProcess child1("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2Child1\\Debug\\lab2Child1.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	CProcess child2("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2Child2\\Debug\\lab2Child2.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	CProcess child3("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2Child3\\Debug\\lab2Child3.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	cout << "Child Processes Activated\n";

	cout << "Waiting for Child1 to terminate\n";
	child1.WaitForProcess();

	cout << "Waiting for Child2 to terminate\n";
	child2.WaitForProcess();

	cout << "Waiting for Child3 to terminate\n";
	child3.WaitForProcess();

	cout << "All processes have ended";

	return 0;
}