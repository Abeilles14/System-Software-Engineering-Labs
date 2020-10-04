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

public:
	WashingMachine(int number);

	void Start();
	void Stop();
	void End();

};



#endif