#include <iostream>

#include "CSwitch.h"

using namespace std;

// Constructors
CSwitch::CSwitch() {
	state = 0;

	cout << "CSwtich Constructor called, switch off\n";
}

CSwitch::CSwitch(int initState) {
	state = initState;

	cout << "CSwtich Constructor called, switch state: " << state << "\n";
}

CSwitch::~CSwitch() {
	cout << "CSwitch destructor called\n";
}

// Accessors
int CSwitch::getState() {
	cout << "Switch state: " << state << "\n";

	return state;
}

void CSwitch::print() {
	cout << "Printing switch state: " << state << "\n";
}

// Mutators
void CSwitch::turnon() {
	state = 1;
}

void CSwitch::turnoff() {
	state = 0;
}