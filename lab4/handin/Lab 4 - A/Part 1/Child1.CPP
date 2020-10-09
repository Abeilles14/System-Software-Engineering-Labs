//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	This example Pocess makes/uses a datapool and reads data out
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include 	"..\\..\rt.h"		// change pathlist to "rt.h" file to suit location on disk

//
//	It's important to realise that all processes accessing the same datapool must
//	describe exactly the same datapool or structure template otherwise corruption
//	of data will occur. Ideally, the structure template would be put into a single header file
//	which would be '#include'd' into each program that used that datapool. However, for
//	simplicity, we have recreated the same template in each process
//
  
struct 	    mydatapooldata {		// start of structure template
	char coffeeShop[20];
	char coffeeSize;
	int coffeeCups;
	int donutsAmount[10];
};						


int   main()
{
	int i ;

	cout << "Child1 attempting to create/use the datapool.....\n";
	CDataPool 		dp("myCoffee", sizeof(struct mydatapooldata)) ;

	struct mydatapooldata 	 *MyDataPool = (struct mydatapooldata *)(dp.LinkDataPool()) ;

	cout << "Child1 linked to datapool at address : " << MyDataPool << ".....\n";

	std::string toWrite = "Tim Hortons";
	for (uint8_t index = 0; index < toWrite.length(); index++) {
		MyDataPool->coffeeShop[index] = toWrite[index];
	}

	cout << "Child1 write value for coffeeShop = " << MyDataPool->coffeeShop << endl;

	MyDataPool->coffeeSize = 'L';

	cout << "Child1 write value for coffeeSize = " << MyDataPool->coffeeSize << endl;
	
	MyDataPool->coffeeCups = 4;

	cout << "Child1 write value for coffeeCups = " << MyDataPool->coffeeCups << endl;

	for (uint8_t index = 0; index < 10; index++) {
		MyDataPool->donutsAmount[index] = index + 1;
	}

	printf("Child1 write values for donutsAmount = ") ;
	for(i=0; i < 10; i ++)
		cout << MyDataPool->donutsAmount[ i ] << " ";
	
	return 0 ;
}