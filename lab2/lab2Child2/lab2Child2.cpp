#include <iostream>
#include "../../rt.h"

int main() {
	for (int i = 0; i < 75; i++) {
		cout << "Child 2 counter: " << i <<"\n";
		Sleep(50);
	}

	return 0;
}