#include "../../rt.h"

int main(int argc, char* argv[]) {

	cout << "argc   count = " << argc << "\n";

	for (int i = 0; i < argc; i++) {			// set up loop to print out all args
		cout << "argv[ " << i << "] = " << argv[i] << "\n";
	}

	for (int i = 0; i < 100; i++) {
		cout << "Child 3 counter: " << i << "\n";
		Sleep(50);
	}

	cout << "Child3 has ended\n\n";

	return 0;
}