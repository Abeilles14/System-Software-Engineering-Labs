#include <iostream>

#include "CLamp3Bulb.h"

using namespace std;

// Constructors
CLamp3Bulb::CLamp3Bulb(int w1, int w2, int w3) {
	lightbulb[0].setwatts(w1);
	lightbulb[1].setwatts(w2);
	lightbulb[2].setwatts(w3);

	lightbulb[0].off();
	lightbulb[1].off();
	lightbulb[2].off();

	lightswitch.turnoff();

	cout << "CLamp3Bulb Constructor called, switch and lightbulb off\n";
}

CLamp3Bulb::~CLamp3Bulb() {
	cout << "CLamp3Bulb destructor called\n";
}

// Accessors
int CLamp3Bulb::getState() {
	int state = lightswitch.getState();

	cout << "Lamp state: " << state << "\n";

	return state;
}

int CLamp3Bulb::getPower() {
	int power_consumed = lightbulb[0].getPower() + lightbulb[1].getPower() + lightbulb[2].getPower();

	cout << "Power consumed: " << power_consumed << "\n";

	return power_consumed;
}

void CLamp3Bulb::print() {
	int state = lightswitch.getState();

	cout << "Printing lamp state: " << state << "\n";
}

// Mutators
void CLamp3Bulb::LampOn() {
	lightbulb[0].on();
	lightbulb[1].on();
	lightbulb[2].on();

	lightswitch.turnon();
}

void CLamp3Bulb::LampOff() {
	lightbulb[0].off();
	lightbulb[1].off();
	lightbulb[2].off();

	lightswitch.turnoff();
}