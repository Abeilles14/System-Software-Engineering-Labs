#include <iostream>
#include "../../rt.h"

using namespace std;

int main() {
	for (int i = 0; i < 50; i++) {
		cout << "Child 1 counter: " << i << "\n";
		Sleep(50);
	}

	cout << "Child1 has ended\n\n";

	return 0;
}