#include <iostream>

#include "CSwitch.h"

using namespace std;

CSwitch::CSwitch() {
	state = 0;

	cout << "CSwtich Constructor called, switch off\n";
}

CSwitch::~CSwitch() {
	cout << "CSwitch destructor called\n";
}

void CSwitch::turnon() {
	state = 1;
}

void CSwitch::turnoff() {
	state = 0;
}

int CSwitch::getState() {
	cout << "switch state: " << state << "\n";

	return state;
}

void CSwitch::print() {
	cout << "printing switch state: " << state << "\n";
}