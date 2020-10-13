#include"../../rt.h"
#include <stdio.h>


struct	mydatapooldata {
	int x;
};

struct	mydatapooldata* TheDataPointer;

int main()
{
	CSemaphore	ps2("PS2", 0, 1);
	CSemaphore	cs2("CS2", 0, 1);

//	Create a datapool and then get a pointer to it

	CDataPool dp1("MyDataPoolName", sizeof(struct mydatapooldata));
	TheDataPointer = (struct mydatapooldata*)(dp1.LinkDataPool()); // get pointer to data pool

	cout << "Consumer Process Running\n";
	for (int i = 0; i < 10; i++) {
		cout << "Hit RETURN to Consume Data\n";
		getchar();

		ps2.Wait();
		cout << "Consumed: " << TheDataPointer->x << '\n';
		cs2.Signal();
	}

	getchar();

	return 0;
}
