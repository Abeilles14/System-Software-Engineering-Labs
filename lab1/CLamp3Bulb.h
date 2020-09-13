#include "CSwitch.h"
#include "Cbulb.h"

#pragma once

#ifndef   __CLamp3Bulb__
#define   __CLamp3Bulb__

class CLamp3Bulb {

public:
	CLamp3Bulb(int w1, int w2, int w3);
	~CLamp3Bulb();

	void LampOn();
	void LampOff();
	void print();

	int getState();
	int getPower();

private:
	CSwitch lightswitch;
	CBulb *lightbulb = new CBulb[3];
};

#endif