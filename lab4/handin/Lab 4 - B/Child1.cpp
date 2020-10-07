#include "..\..\rt.h"

struct coffeeShop {
	char name[20];
	char size;
	int cups;
};


int main() {
	struct coffeeShop coffee;

	cout << "Child1 Process Creating the Pipeline\n";

	CPipe p1("Pipe1", 1024);

	cout << "Parent Process Creating Child Process to Read from Pipeline\n";
	
	strcpy_s(coffee.name,"Espresso");

	p1.Write(&coffee.name[0], sizeof(coffee.name));
	cout << "Child1 Writing " << coffee.name << " to pipeline\n";

	coffee.size = 'L';
	p1.Write(&coffee.size, sizeof(coffee.size));
	cout << "Child1 Writing " << coffee.size << " to pipeline\n";

	coffee.cups = 5;
	p1.Write(&coffee.cups, sizeof(coffee.cups));
	cout << "Child1 Writing " << coffee.cups << " to pipeline\n";

	Sleep(10000);

	return 0;
}