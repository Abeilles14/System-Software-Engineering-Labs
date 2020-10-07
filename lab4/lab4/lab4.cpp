#include "..\..\rt.h"

UINT __stdcall Thread1(void* args);
UINT __stdcall Thread2(void* args);

struct coffeeShop {
	char name[10];
	char size;
	int cups;
};

struct donutShop {
	char name[14];
	int amount;
};

char KeyData;

UINT __stdcall Thread1(void* args) {
	struct coffeeShop coffee = *(struct coffeeShop*)(args);

	CPipe p1("Pipe1", 1024);		// create pipeline 1 from thread 1

	while (true) {
		p1.Read(&coffee.name, sizeof(char[10]));
		cout << "Parent Thread 1: Read " << coffee.name << " from Pipe1\n";

		p1.Read(&coffee.size, sizeof(char));
		cout << "Parent Thread 1: Read " << coffee.size << " from Pipe1\n";

		p1.Read(&coffee.cups, sizeof(int));
		cout << "Parent Thread 1: Read " << coffee.cups << " from Pipe1\n";
	}

	return 0;
}

UINT __stdcall Thread2(void* args) {
	struct donutShop donut = *(struct donutShop*)(args);

	CPipe p2("Pipe2", 1024);		// create pipeline 2 from thread 2

	while (true) {
		p2.Read(&donut.name, sizeof(char[14]));
		cout << "Parent Thread 2: Read " << donut.name << " from Pipe2\n";

		p2.Read(&donut.amount, sizeof(int));
		cout << "Parent Thread 2: Read " << donut.amount << " from Pipe2\n";
	}

	return 0;
}

int main() {
	struct coffeeShop coffee;
	struct donutShop donut;

	cout << "Parent Process Creating 2 Child Processes\n";

	CProcess child1("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab4\\lab4\\Debug\\Child1.exe", 	// create child process
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	CProcess child2("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab4\\lab4\\Debug\\Child2.exe", 	// create child process
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	cout << "Parent Process Creating 2 Child threads to read from their Pipeline\n";

	CThread t1(Thread1, ACTIVE, &coffee);
	CThread t2(Thread2, ACTIVE, NULL);

	while (1) {
		KeyData = _getch();		// prevent process from exiting + it's fun
		cout << "Parent Thread Read " << KeyData << " from keyboard\n";
	}

	return 0;			
}

