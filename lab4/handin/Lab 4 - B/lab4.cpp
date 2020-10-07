#include "..\..\rt.h"

struct coffeeShop {
	char name[20];
	char size;
	int cups;
};

struct donutShop {
	char name[20];
	int amount;
};

char KeyData;

UINT __stdcall Thread1(void*) {
	struct coffeeShop coffee;

	CPipe p1("Pipe1", 1024);		// create pipeline 1 from thread 1

	while (true) {
		p1.Read(&coffee.name[0], sizeof(coffee.name));
		cout << "Parent Thread 1: Read "<< coffee.name << " from Pipe1\n";

		Sleep(2000);

		p1.Read(&coffee.size, sizeof(char));
		cout << "Parent Thread 1: Read " << coffee.size << " from Pipe1\n";

		Sleep(2000);

		p1.Read(&coffee.cups, sizeof(int));
		cout << "Parent Thread 1: Read " << coffee.cups << " from Pipe1\n";
	}

	return 0;
}

UINT __stdcall Thread2(void*) {
	struct donutShop donut;

	CPipe p2("Pipe2", 1024);		// create pipeline 2 from thread 2

	while (true) {
		Sleep(2000);

		p2.Read(&donut.name[0], sizeof(donut.name));
		cout << "Parent Thread 2: Read " << donut.name << " from Pipe1\n";

		Sleep(4000);

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

	while (true) {		// prevent process from exiting + it's fun
		KeyData = _getch();
		cout << "Parent Thread Read " << KeyData << " from keyboard\n";
	}

	return 0;			
}

