#include "../../rt.h"

int main(int argc, char* argv[]) {

	cout << "argc   count = " << argc << "\n";

	for (int i = 0; i < argc; i++) {			// set up loop to print out all args
		cout << "argv[ " << i << "] = " << argv[i] << "\n";
	}

	for (int i = 0; i < 75; i++) {
		cout << "Child 2 counter: " << i <<"\n";
		Sleep(50);
	}

	cout << "Child2 has ended\n\n";

	return 0;
}