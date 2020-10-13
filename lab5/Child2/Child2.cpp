#include"../../rt.h"
#include <stdio.h>

struct	mydatapooldata {
	int x;
};

struct	mydatapooldata* TheDataPointer2;

int main()
{
	CSemaphore	ps2("PS2", 0, 1);
	CSemaphore	cs2("CS2", 1, 1);

//	Create a datapool and then get a pointer to it

	CDataPool dp1("MyDataPoolName2", sizeof(struct mydatapooldata));
	TheDataPointer2 = (struct mydatapooldata*)(dp1.LinkDataPool()); // get pointer to data pool

	cout << "Producer Process 2 Running\n";

	for (int i = 0; i < 10; i++) {

		cs2.Wait();

		cout << "Hit RETURN to Produce Data\n";
		getchar();

		TheDataPointer2->x = i;
		cout << "Produced: " << TheDataPointer2->x << '\n';

		ps2.Signal();
	}

	getchar();

	return 0;
}
