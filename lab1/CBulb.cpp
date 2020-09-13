#include <iostream>

#include "CBulb.h"

using namespace std;

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

void CBulb::print() {
	cout << "printing lightbulb state: " << state <<"\n";
}

void CBulb::on() {
	cout << "on\n";
	state = 1;
}

void CBulb::off() {
	cout << "off\n";
	state = 0;
}

void CBulb::setwatts(int watts_value) {
	watts = watts_value;
}

int CBulb::getstate() {
	cout << "state: " << state << "\n";
	return state;
}

int CBulb::getPower() {
	cout << "watts: " << watts << "\n";
	return watts;
}

/*void CBulb::setstate(int value) {
	state = value;
}*/