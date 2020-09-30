#include "..\..\rt.h"

int main(int argc, char *argv[])
{
	int i ;

	cout << "argc   count = " << argc << "\n";
	for (int i = 0; i < argc; i++)			// set up loop to print out all args
		cout << "argv[ " << i << "] = " << argv[i] << "\n";


	for( i = 0; i < 300; i ++) {
		cout << "Hello from child process 3....\n";
		Sleep(50);
	}

	return 0 ;		// exit child program by returning status value 0
				// Note we could also call exit(0) to achieve the same thing
}