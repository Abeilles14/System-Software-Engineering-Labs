#include 	"..\rt.h"		// change pathlist to "rt.h" file to suit location on disk

// Let's suppose the data we want to put in the datapool is complex, i.e not just a simple
// int or char. The easiest way to store complex data is to introduce a structure template
// describing the names and types of the data we wich to group together as shown below
//  which includes three variables, two simple integers and an array of 10 integers
  
struct 	    mydatapooldata 	{		// start of structure template
	char coffeeShop[20];
	char coffeeSize;
	int coffeeCups;
	int donutsAmount[10];
} ;							// end of structure template

int 	main()
{
	cout << "Parent attempting to create/use the datapool myCoffee.....\n";
	CDataPool 		dp("myCoffee", sizeof(struct mydatapooldata)) ;
	
	struct mydatapooldata 	 *MyDataPool = (struct mydatapooldata *)(dp.LinkDataPool()) ;

	printf("Parent linked to datapool at address %p.....\n", MyDataPool) ;

// Now that we have the pointer to the datapool, we can put data into it

	cout << "Parent leaving all of the work to the children.....\n";

//	Now that we have created the data pool and have stored data in it, it is safe to create
//	a child process that can access the data

	CProcess p1("C:\\RTExamples\\Q3 - InterProcessCommunicationUsingDataPools\\Child1\\debug\\Q4.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,			// priority
		PARENT_WINDOW,						// process has its own window
		ACTIVE							// process is active immediately
	) ;

	p1.WaitForProcess();		// need to wait for process 1 to finish writing data before children can access

	CProcess p2("C:\\RTExamples\\Q3 - InterProcessCommunicationUsingDataPools\\Child2\\debug\\Q4.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,			// priority
		PARENT_WINDOW,						// process has its own window
		ACTIVE							// process is active immediately
	);

	CProcess p3("C:\\RTExamples\\Q3 - InterProcessCommunicationUsingDataPools\\Child3\\debug\\Q4.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,			// priority
		PARENT_WINDOW,						// process has its own window
		ACTIVE							// process is active immediately
	);

	p2.WaitForProcess();		// wait for the child process to Terminate
	p3.WaitForProcess();		// wait for the child process to Terminate

	return 0 ;				// CDataPool object 'dp' destroyed here
}