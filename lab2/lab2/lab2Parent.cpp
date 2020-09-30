#include 	"..\..\rt.h"			// change pathlist to this header file according to where it is stored


int main() {
	cout << "Creating Child Processes.....\n";

	CProcess p1("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2\\Debug\\lab2Child1.exe I'm getting these strings from Q1Parent",	// pathlist to child program executable				
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);


	CProcess p2("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2\\Debug\\lab2Child2.exe I'm getting these strings from Q1Parent",	// pathlist to child program executable				
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);

	CProcess p3("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2\\Debug\\lab2Child3.exe I'm getting these strings from Q1Parent",	// pathlist to child program executable	plus some arguments		
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE
	);

	cout << "Child Processes Activated.....\n";

	cout << "Waiting For Child1 to Terminate.....\n";
	p1.WaitForProcess();

	cout << "Waiting For Child2 to Terminate.....\n";
	p2.WaitForProcess();					// wait for the child process to end

	cout << "Waiting For Child3 to Terminate.....\n";
	p3.WaitForProcess();					// wait for the child process to end

	return 0;
}