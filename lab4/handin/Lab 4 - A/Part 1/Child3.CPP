//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	This example Pocess makes/uses a datapool and reads data out
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include 	"..\\..\rt.h"		// change pathlist to "rt.h" file to suit location on disk

struct 	    mydatapooldata {		// start of structure template
	char coffeeShop[20];
	char coffeeSize;
	int coffeeCups;
	int donutsAmount[10];
};							// end of structure template

int   main()
{
	int i;

	cout << "\nChild3 attempting to create/use the datapool myCoffee.....\n";
	CDataPool 		dp("myCoffee", sizeof(struct mydatapooldata));

	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());

	cout << "Child3 linked to datapool at address : " << MyDataPool << ".....\n";

	cout << "Child3 read value for coffeeSize: " << MyDataPool->coffeeSize << std::endl;

	cout << "Child3 Read values for coffeeCups: " << MyDataPool->coffeeCups << std::endl;

	return 0;
}