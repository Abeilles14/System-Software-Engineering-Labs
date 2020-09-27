#include <iostream>
#include "../../rt.h"

using namespace std;

int main() {
	for (int i = 0; i < 100; i++) {
		cout << "Child 3 counter: " << i << "\n";
		Sleep(50);
	}

	cout << "Child3 has ended\n\n";

	return 0;
}