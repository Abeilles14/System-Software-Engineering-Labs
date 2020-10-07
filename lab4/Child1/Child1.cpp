#include "..\..\rt.h"

struct coffeeShop {
	const char* name[10];
	char size;
	int cups;
};

int main() {
	struct coffeeShop coffee;

	cout << "Child1 Process Creating the Pipeline\n";

	CPipe p1("Pipe1");

	cout << "Parent Process Creating Child Process to Read from Pipeline\n";
	
	coffee.name[10] = "Espresso";
	p1.Write(&coffee.name[0], sizeof(coffee.name));
	cout << "Child1 Writing " << coffee.name << " to pipeline\n";

	Sleep(3000);

	coffee.size = 'L';
	p1.Write(&coffee.size, sizeof(coffee.size));
	cout << "Child1 Writing " << coffee.size << " to pipeline\n";

	Sleep(3000);

	coffee.cups = 5;
	p1.Write(&coffee.cups, sizeof(coffee.cups));
	cout << "Child1 Writing " << coffee.cups << " to pipeline\n";

	Sleep(10000);

	return 0;
}