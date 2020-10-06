#include "..\..\rt.h"

struct mydatapooldata {
	char coffeeSize;
	int coffeeCups;
	int countTimbits[10];	// gotta make sure all 10 are there yknow
};

int main() {
	cout << "Child attempting to create/use the datapool\n";
	
	CDataPool dp("Coffee Shop Datapool", sizeof(struct mydatapooldata));	// creating datapool

	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());	//ptr to datapool location in memory to access

	cout << "Child linked to datapool at address : " << MyDataPool << "\n";

	cout << "Child Read value for coffeeSize = " << MyDataPool->coffeeSize << endl;

	cout << "Child Read value for coffeeCups = " << MyDataPool->coffeeCups << endl;

	printf("Child Read values for countTimbits array = ");
	for (int i = 0; i < 10; i++) {
		cout << MyDataPool->countTimbits[i] << " ";
	}

	getchar();	// wait for char/enter

	return 0;
}