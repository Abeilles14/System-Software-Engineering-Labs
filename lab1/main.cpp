#include <stdio.h>
#include <iostream>

#include "CBulb.h"
#include "CSwitch.h"
#include "CLamp3Bulb.h"

int main() {
	CBulb lightbulb(20);
	CSwitch lightswitch;
	CLamp3Bulb lamp(5, 10, 15);

	std::cout << "\nBEGINNING OF TESTS\n";

	// lightbulb
	std::cout << "\nLIGHTBULB TESTS:\n";
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
	lightswitch.print();

	lightswitch.turnon();
	lightswitch.getState();
	lightswitch.print();
	lightswitch.turnoff();

	// lamp
	std::cout << "\nLAMP TESTS:\n";
	lamp.LampOn();
	lamp.print();
	lamp.LampOff();
	lamp.getState();
	lamp.getPower();

	std::cout << "\nEND OF TESTS\n";

	return 0;
}
