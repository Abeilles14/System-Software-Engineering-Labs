#include <iostream>

#include "CLamp3Bulb.h"

using namespace std;

// Constructors
CLamp3Bulb::CLamp3Bulb(int w1, int w2, int w3) {
	
	myBulbs[0] = new CBulb(w1);
	myBulbs[1] = new CBulb(w2);
	myBulbs[2] = new CBulb(w3);

	myBulbs[0]->setwatts(w1);
	myBulbs[1]->setwatts(w2);
	myBulbs[2]->setwatts(w3);

	myBulbs[0]->off();
	myBulbs[1]->off();
	myBulbs[2]->off();

	mySwitch = new CSwitch(0);
	mySwitch->turnoff();

	cout << "CLamp3Bulb Constructor called, switch and lightbulb off\n";
}

CLamp3Bulb::CLamp3Bulb(const CLamp3Bulb& LampToCopy)
{
	myBulbs[0] = new CBulb();
	myBulbs[1] = new CBulb();
	myBulbs[2] = new CBulb();
	mySwitch = new CSwitch();

	*myBulbs[0] = *LampToCopy.myBulbs[0];
	*myBulbs[1] = *LampToCopy.myBulbs[1];
	*myBulbs[2] = *LampToCopy.myBulbs[2];

	*mySwitch = *LampToCopy.mySwitch;
}


CLamp3Bulb::~CLamp3Bulb() {
	delete myBulbs[0];
	delete myBulbs[1];
	delete myBulbs[2];

	delete mySwitch;

	cout << "CLamp3Bulb destructor called\n";
}

// Accessors
int CLamp3Bulb::getState() {
	int state = mySwitch->getState();

	cout << "Lamp state: " << state << "\n";

	return state;
}

int CLamp3Bulb::getPower() {
	int power_consumed = myBulbs[0]->getPower() + myBulbs[1]->getPower() + myBulbs[2]->getPower();

	cout << "Power consumed: " << power_consumed << "\n";

	return power_consumed;
}

void CLamp3Bulb::print() {
	int state = mySwitch->getState();

	cout << "Printing lamp state: " << state << "\n";
}

// Mutators
void CLamp3Bulb::LampOn() {
	myBulbs[0]->on();
	myBulbs[1]->on();
	myBulbs[2]->on();

	mySwitch->turnon();
}

void CLamp3Bulb::LampOff() {
	myBulbs[0]->off();
	myBulbs[1]->off();
	myBulbs[2]->off();

	mySwitch->turnoff();
}

CBulb* CLamp3Bulb::exchange(CBulb* newBulb, int bulbNumber) {
	CBulb* tempBulbPtr;

	tempBulbPtr = myBulbs[bulbNumber];
	myBulbs[bulbNumber] = newBulb;

	return tempBulbPtr;
}