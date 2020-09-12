#include <iostream>

#include "CBulb.h"

using namespace std;

void CBulb::printstate() {
	cout << "lightbulb state:" << state;
}

void CBulb::setstate(int value) {
	state = value;
}