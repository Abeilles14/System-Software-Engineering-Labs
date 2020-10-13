#include"../../rt.h"
#include <stdio.h>

struct	mydatapooldata {
	int x;
};

struct	mydatapooldata* TheDataPointer;

int main()
{
	CSemaphore	ps1("PS1", 0, 1);
	CSemaphore	cs1("CS1", 1, 1);

//	Create a datapool and then get a pointer to it

	CDataPool dp1("MyDataPoolName", sizeof(struct mydatapooldata));
	TheDataPointer = (struct mydatapooldata*)(dp1.LinkDataPool()); // get pointer to data pool

	cout << "Consumer Process Running\n";

	for (int i = 0; i < 10; i++) {
		cout << "Hit RETURN to Consume Data\n";
		getchar();

		ps1.Wait();

		cout << "Consumed: " << TheDataPointer->x << '\n';

		cs1.Signal();
	}

	getchar();

	return 0;
}
