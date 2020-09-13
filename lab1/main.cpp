#include <stdio.h>

#include "CBulb.h"
#include "CSwitch.h"

int main() {
	CBulb lightbulb(20);
	CSwitch lightswitch;

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

	return 0;
}
