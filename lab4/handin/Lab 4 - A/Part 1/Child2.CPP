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
	int i ;

	cout << "\nChild2 attempting to create/use the datapool myCoffee.....\n";
	CDataPool 		dp("myCoffee", sizeof(struct mydatapooldata)) ;
	
	struct mydatapooldata 	 *MyDataPool = (struct mydatapooldata *)(dp.LinkDataPool()) ;

	cout << "Child2 linked to datapool at address : " << MyDataPool << ".....\n";

	cout << "Child2 read value for coffeeShop: " << MyDataPool->coffeeShop << std::endl;

	printf("Child2 Read values for donutsAmount = ") ;
	for(i=0; i < 10; i ++)
		cout << MyDataPool->donutsAmount[ i ] << " ";
	
	return 0 ;
}