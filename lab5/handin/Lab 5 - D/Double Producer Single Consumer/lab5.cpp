#include	"../../rt.h"
#include 	<stdio.h>

struct mydatapooldata {
	int x;
};

struct	mydatapooldata* TheDataPointer1;		// pointer to the actual data pool
struct	mydatapooldata* TheDataPointer2;		// pointer to the actual data pool

int main()
{
	CSemaphore	ps1("PS1", 0, 1);    // semaphore with initial value 0 and max value 1
	CSemaphore	ps2("PS2", 0, 1);    // semaphore with initial value 0 and max value 1
	CSemaphore	cs1("CS1", 1, 1);    // semaphore with initial value 1 and max value 1
	CSemaphore	cs2("CS2", 1, 1);    // semaphore with initial value 1 and max value 1

//	Create a datapool and then get a pointer to it

	CDataPool dp1("MyDataPoolName1", sizeof(struct mydatapooldata));
	CDataPool dp2("MyDataPoolName2", sizeof(struct mydatapooldata));

	TheDataPointer1 = (struct mydatapooldata*)dp1.LinkDataPool();
	TheDataPointer2 = (struct mydatapooldata*)dp2.LinkDataPool();

	CProcess p1("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab5\\lab5\\Debug\\Child1.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,	
		OWN_WINDOW,			
		ACTIVE		
	);

	CProcess p2("C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab5\\lab5\\Debug\\Child2.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,		
		OWN_WINDOW,					
		ACTIVE					
	);

	printf("Consumer Process Running\n");

	for (;;) {
		if (ps1.Read() > 0) {
			ps1.Wait();

			cout << "Hit RETURN to Consume Data from Datapool 1\n";
			getchar();
			cout << "Datapool 1 consumed " << TheDataPointer1->x << "\n";

			cs1.Signal();
		}

		if (ps2.Read() > 0) {
			ps2.Wait();

			cout << "Hit RETURN to Consume Data from Datapool 2\n";
			getchar();
			cout << "Datapool 2 consumed " << TheDataPointer2->x << "\n";

			cs2.Signal();
		}
	}

	p1.WaitForProcess();
	p2.WaitForProcess();

	return 0;	
}