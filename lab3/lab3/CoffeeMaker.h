#include "../../rt.h"

#ifndef   __CoffeeMaker__
#define   __CoffeeMaker__

class CoffeeMaker : public ActiveClass{
private:
	int machineNumber;
	int currentState;
	bool start;
	bool running;

	int main(void);
	UINT __stdcall GrindCoffee(void* args);
	UINT __stdcall AddMilkCream(void* args);

public:
	CoffeeMaker(int number);

	void Start();
	void Stop();
	void End();

};

#endif