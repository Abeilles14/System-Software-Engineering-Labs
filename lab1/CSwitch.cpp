#include <iostream>

#include "CSwitch.h"

using namespace std;

CSwitch::CSwitch() {
	state = 0;
	cout << "CSwtich Constructor called, swtich off\n";
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
	return state;
}

void CSwitch::print() {
	cout << "printing switch state: " << state << "\n";
}