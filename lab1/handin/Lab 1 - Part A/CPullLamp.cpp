#include "CPullLamp.h"
#include <iostream>

// Constructors
CPullLamp::CPullLamp(int w1, int w2, int w3) : CLamp3Bulb(w1, w2, w3) {
	std::cout << "CPullLamp constructor calledc\n";
}

// Mutators
void CPullLamp::toggle() {
	if (getState() == 0)	// if lamp is off (another inherited function)
		CLamp3Bulb::LampOn();	// turn on CPulledLamp using inherited function
	else
		CLamp3Bulb::LampOff();
}