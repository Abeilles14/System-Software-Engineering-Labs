#include <iostream>
#include "../../rt.h"

int main() {
	for (int i = 0; i < 50; i++) {
		cout << "Child 1 counter: " << i << "\n";
		Sleep(50);
	}

	return 0;
}