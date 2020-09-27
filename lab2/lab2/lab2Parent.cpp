#include <iostream>
#include "../../rt.h"

using namespace std;

int main() {
	cout << "Creating 3 Child Processes\n";

	CProcess child1("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2\\Debug\\lab2Child1.exe",
		NORMAL_PRIORITY_CLASS,
		PARENT_WINDOW,
		ACTIVE
	);

	CProcess child2("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2\\Debug\\lab2Child2.exe",
		NORMAL_PRIORITY_CLASS,
		PARENT_WINDOW,
		SUSPENDED
	);

	CProcess child3("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2\\Debug\\lab2Child3.exe",
		NORMAL_PRIORITY_CLASS,
		PARENT_WINDOW,
		ACTIVE
	);

	cout << "Child Processes Activated\n";

	cout << "\nChild 2 is suspended\n";
	SLEEP(3000);
	cout << "\nChild2 is resuming, Child3 is suspended\n";
	child2.Resume();
	child3.Suspend();
	SLEEP(3000);
	cout << "\nChild3 is resuming\n";
	child3.Resume();

	cout << "\nWaiting for Child1 to terminate\n";
	child1.WaitForProcess();

	cout << "\nWaiting for Child2 to terminate\n";
	child2.WaitForProcess();

	cout << "\nWaiting for Child3 to terminate\n";
	child3.WaitForProcess();

	cout << "\nAll processes have ended\n";

	return 0;
}