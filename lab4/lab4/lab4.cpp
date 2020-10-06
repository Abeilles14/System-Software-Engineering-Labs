#include "..\..\rt.h"

struct mydatapooldata {
	char coffeeSize;
	int coffeeCups;
	int countTimbits[10];	// gotta make sure all 10 are there yknow
};

int main() {
	cout << "Parent attempting to create/use the datapool\n";

	CDataPool dp("Coffee Shop Datapool", sizeof(struct mydatapooldata));	// creating datapool

	struct mydatapooldata *MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());	//ptr to datapool location in memory to access

	printf("Parent linked to datapool at address %p\n", MyDataPool);

	cout << "Parent Writing value 'Tim Hortons' to coffeeSize variable\n";
	MyDataPool->coffeeSize = 'L';

	cout << "Parent Writing value 4 to coffeeCups variable\n";
	MyDataPool->coffeeCups = 4;

	cout << "Parent Writing value '1 2 3 4 5 6 7 8 9 10' to donutsAmount variable\n";
	for (int i = 1; i <= 10; i++) {
		MyDataPool->countTimbits[i] = i;
	}

	getchar();	// wait for char/enter

	CProcess p1("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab4\\lab4\\Debug\\Child1.exe", 	// create child process
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	p1.WaitForProcess();	

	return 0;			

}