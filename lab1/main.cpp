#include <stdio.h>

#include "CBulb.h"
#include "CSwitch.h"
#include "CLamp3Bulb.h"

int main() {
	CBulb lightbulb(20);
	CSwitch lightswitch;
	CLamp3Bulb lamp(5, 10, 15);

	// lightbulb
	lightbulb.print();
	lightbulb.getPower();

	lightbulb.off();
	lightbulb.setwatts(0);
	lightbulb.getstate();
	lightbulb.getPower();

	lightbulb.on();
	lightbulb.setwatts(5);
	lightbulb.getstate();
	lightbulb.getPower();

	//switch
	lightswitch.print();

	lightswitch.turnon();
	lightswitch.getState();
	lightswitch.print();
	lightswitch.turnoff();

	//lamp
	lamp.LampOn();
	lamp.print();
	lamp.LampOff();
	lamp.getState();
	lamp.getPower();

	return 0;
}
