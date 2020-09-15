#include "CSwitch.h"
#include "Cbulb.h"

#ifndef   __CLamp3Bulb__
#define   __CLamp3Bulb__

class CLamp3Bulb {

private:
	CSwitch lightswitch;
	CBulb* lightbulb = new CBulb[3];

public:
	// Constructors
	CLamp3Bulb(int w1, int w2, int w3);
	~CLamp3Bulb();

	// Accessors
	int getState();
	int getPower();
	void print();

	// Mutators
	void LampOn();
	void LampOff();
};

#endif