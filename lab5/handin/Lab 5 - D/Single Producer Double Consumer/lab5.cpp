#include	"../../rt.h"
#include 	<stdio.h>

struct mydatapooldata {
	int x;
};

struct	mydatapooldata* TheDataPointer;		// pointer to the actual data pool

int main()
{
	CSemaphore	ps1("PS1", 0, 1);    // semaphore with initial value 0 and max value 1
	CSemaphore	ps2("PS2", 0, 1);    // semaphore with initial value 0 and max value 1
	CSemaphore	cs1("CS1", 1, 1);    // semaphore with initial value 1 and max value 1
	CSemaphore	cs2("CS2", 1, 1);    // semaphore with initial value 1 and max value 1

//	Create a datapool and then get a pointer to it

	CDataPool dp1("MyDataPoolName", sizeof(struct mydatapooldata));
	TheDataPointer = (struct mydatapooldata*)dp1.LinkDataPool();	

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

	printf("Producer Process Running\n");

	for (int i = 0; i < 10; i++) {
		cs1.Wait();
		cs2.Wait();

		TheDataPointer->x = i;			// generate data and store in datapool

		ps1.Signal();
		ps2.Signal();

		cout << "Produced " << i << "\n";
	}

	p1.WaitForProcess();
	p2.WaitForProcess();

	return 0;	
}