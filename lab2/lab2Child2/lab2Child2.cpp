#include <iostream>
#include "../../rt.h"

using namespace std;

int main() {
	for (int i = 0; i < 75; i++) {
		cout << "Child 2 counter: " << i <<"\n";
		Sleep(50);
	}

	cout << "Child2 has ended\n\n";

	return 0;
}