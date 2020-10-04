#include "../../rt.h"

#ifndef   __WashingMachine__
#define   __WashingMachine__

class WashingMachine : public ActiveClass {
private:
	int machineNumber;
	int currentState;
	bool start;
	bool running;

	int main(void);
	UINT __stdcall WaterInletValve(void* args);
	UINT __stdcall Motor(void* args);

public:
	WashingMachine(int number);

	void Start();
	void Stop();
	void End();

};



#endif