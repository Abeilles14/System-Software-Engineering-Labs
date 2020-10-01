#include <stdio.h>
#include <iostream>

#include "CBulb.h"
#include "CSwitch.h"
#include "CLamp3Bulb.h"
#include "CPullLamp.h"
#include "CList.h"

int main() {

	std::cout << "\nBEGINNING OF TESTS\n";

	// linked list tests
	std::cout << "\nLINKED LISTS TESTS:\n";
	CList list;

	list.insertNode(10);
	list.insertNode(20);
	list.insertNode(30);

	list.getData(0);
	list.deleteNode();
	list.getData(0);
	list.deleteNode();
	list.getData(0);
	list.deleteNode();
	list.getData(0);

	std::cout << "\nEND OF TESTS\n";

	return 0;
}
