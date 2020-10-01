#ifndef __CPullLamp__ 
#define __CPullLamp__

#include "CLamp3Bulb.h"

class CPullLamp : public CLamp3Bulb
{
private:
	void LampOn() { };		// empty private function
	void LampOff() { };		// empty private function

public:
	// Constructors
	CPullLamp(int w1, int w2, int w3);

	// Mutators
	void toggle();
};

#endif // __CPullLamp__