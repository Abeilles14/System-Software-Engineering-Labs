#include <stdio.h>

#include "CBulb.h"

int main() {
	CBulb lightbulb(20);

	lightbulb.printstate();
	lightbulb.getPower();

	lightbulb.off();
	lightbulb.setwatts(0);
	lightbulb.getstate();
	lightbulb.getPower();

	lightbulb.on();
	lightbulb.setwatts(5);
	lightbulb.getstate();
	lightbulb.getPower();

	return 0;
}
