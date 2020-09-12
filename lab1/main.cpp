#include <stdio.h>

#include "CBulb.h"

int main() {
	CBulb lightbulb;

	lightbulb.setstate(0);
	lightbulb.printstate();

	return 0;
}
