#include <stdio.h>
#include <iostream>

#include "CBulb.h"
#include "CSwitch.h"
#include "CLamp3Bulb.h"
#include "CPullLamp.h"
#include "CList.h"

int main() {

	std::cout << "\nBEGINNING OF TESTS\n";

	// lightbulb
	std::cout << "\nLIGHTBULB TESTS:\n";
	CBulb lightbulb(20);

	lightbulb.print();
	lightbulb.getPower();

	lightbulb.off();
	lightbulb.getstate();
	lightbulb.getPower();

	lightbulb.on();
	lightbulb.getstate();
	lightbulb.getPower();

	lightbulb.setwatts(5);
	lightbulb.getPower();

	// switch
	std::cout << "\nSWITCH TESTS:\n";
	CSwitch lightswitch;

	lightswitch.print();
	lightswitch.turnon();
	lightswitch.getState();
	lightswitch.print();
	lightswitch.turnoff();

	// lamp
	std::cout << "\nLAMP TESTS:\n";
	CLamp3Bulb lamp(5, 10, 15);

	lamp.LampOn();
	lamp.print();
	lamp.LampOff();
	lamp.getState();
	lamp.getPower();

	// lamp bulb exchange
	std::cout << "\nLAMP BULB EXCHANGE TESTS:\n";
	CBulb* bulb1 = new CBulb(60);

	bulb1 = lamp.exchange(bulb1, 0);
	lamp.getPower();
	delete bulb1;

	// lamp copy consctructor
	std::cout << "\nLAMP COPY TESTS:\n";
	CLamp3Bulb copiedLamp(lamp);

	copiedLamp.print();
	copiedLamp.getState();
	copiedLamp.getPower();

	// pull lamp tests
	std::cout << "\nPULL LAMP TESTS:\n";
	CPullLamp pullLamp(100, 100, 100);	// create a Pull Lamp with 100 watt bulbs

	pullLamp.toggle();
	printf("Power of Lamp = %d\n", pullLamp.getPower());	// print power

	pullLamp.toggle();
	printf("Power of Lamp = %d\n", pullLamp.getPower());	// print power

	pullLamp.toggle();
	printf("Power of Lamp = %d\n", pullLamp.getPower());	// print power

	// linked list and template tests
	std::cout << "\nLINKED LISTS & TEMPLATE TESTS:\n";
	CList<int> L1;

	L1.insertNode(5);
	L1.insertNode(20);
	L1.insertNode(30);

	L1.getData(0);
	L1.deleteNode();
	L1.getData(0);

	std::cout << "\nEND OF TESTS\n";

	return 0;
}
