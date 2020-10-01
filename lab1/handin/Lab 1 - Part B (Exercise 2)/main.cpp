#include <stdio.h>
#include <iostream>

#include "CBulb.h"
#include "CSwitch.h"
#include "CLamp3Bulb.h"
#include "CPullLamp.h"
#include "CList.h"

int main() {

	std::cout << "\nBEGINNING OF TESTS\n";

	// template tests
	std::cout << "\nTEMPLATE TESTS:\n";
	CBulb b1(100);		// create a 100 watt bulb
	CBulb b2(200);		// create a 100 watt bulb
	CBulb b3(300);		// create a 100 watt bulb
	CSwitch s1;
	CSwitch s2;
	CSwitch s3;

	CList <CBulb*> L2;		// A list that holds pointers to CBulb objects
	CList <CSwitch*> L3;		// A list that holds pointers to CSwitch objects

	cout << endl;

	L2.insertNode(&b1);			// Correct: add a pointer to bulb b1 to the list
	L2.insertNode(&b2);	
	L2.insertNode(&b3);		

	L3.insertNode(&s1);			// Correct: add a pointer to switch s1 to the list
	L3.insertNode(&s2);			
	L3.insertNode(&s3);		

	cout << endl;

	std::cout << "First bulb of list L2 power: " << L2.getData(0)->getPower();
	std::cout << "Second bulb of list L2 power: " << L2.getData(1)->getPower();
	std::cout << "Third bulb of list L2 power: " << L2.getData(2)->getPower();

	cout << endl;
	cout << endl;

	// Turn middle switch on
	L3.getData(1)->turnon();

	std::cout << "First bulb of list L3 state: " << L3.getData(0)->getState();
	std::cout << "Second bulb of list L3 state: " << L3.getData(1)->getState();
	std::cout << "Third bulb of list L3 state: " << L3.getData(2)->getState();

	cout << endl;


	std::cout << "\nEND OF TESTS\n\n";

	return 0;
}
