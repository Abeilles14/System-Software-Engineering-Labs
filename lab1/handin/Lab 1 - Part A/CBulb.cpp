#include <iostream>

#include "CBulb.h"

using namespace std;

// Constructors
CBulb::CBulb(int watts_value) {
	state = 1;
	watts = watts_value;
	cout << "CBulb Constructor called, lightbulb on\n";
}

CBulb::CBulb() {
	state = 0;
	watts = 0;
	cout << "CBulb Default Constructor called, lightbulb off, watts is 0\n";
}

CBulb::~CBulb() {
	cout << "CBulb destructor called\n";
}

// Accessors
int CBulb::getPower() {
	if (!state) {
		cout << "Bulb watts: 0" << watts << "\n";
		return 0;
	}
	cout << "Bulb watts: " << watts << "\n";
	return watts;
}

int CBulb::getstate() {
	cout << "Bulb state: " << state << "\n";

	return state;
}

void CBulb::print() {
	cout << "Printing lightbulb state: " << state <<"\n";
}

// Mutators
void CBulb::on() {
	state = 1;

	cout << "On\n";
}

void CBulb::off() {
	state = 0;

	cout << "Off\n";
}

void CBulb::setwatts(int watts_value) {
	watts = watts_value;
}

/*void CBulb::setstate(int value) {
	state = value;
}*/