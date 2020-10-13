#include"../../rt.h"
#include <stdio.h>

struct	mydatapooldata {
	int x;
};

struct	mydatapooldata* TheDataPointer1;

int main()
{
	CSemaphore	ps1("PS1", 0, 1);
	CSemaphore	cs1("CS1", 1, 1);

//	Create a datapool and then get a pointer to it

	CDataPool dp1("MyDataPoolName1", sizeof(struct mydatapooldata));
	TheDataPointer1 = (struct mydatapooldata*)(dp1.LinkDataPool()); // get pointer to data pool

	cout << "Producer Process 1 Running\n";

	for (int i = 0; i < 10; i++) {

		cs1.Wait();

		cout << "Hit RETURN to Produce Data\n";
		getchar();

		TheDataPointer1->x = i;
		cout << "Produced: " << TheDataPointer1->x << '\n';

		ps1.Signal();
	}

	getchar();

	return 0;
}
