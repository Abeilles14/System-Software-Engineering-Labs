#include <iostream>
#include "..\rt.h"

int main() {
	for (int i = 0; i < 100; i++) {
		cout << "Child 1 counter: " << i;
		Sleep(50);
	}

	return 0;
}