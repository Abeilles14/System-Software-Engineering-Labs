#include <iostream>
#include "../../rt.h"

int main() {
	for (int i = 0; i < 100; i++) {
		cout << "Child 3 counter: " << i << "\n";
		Sleep(50);
	}

	return 0;
}