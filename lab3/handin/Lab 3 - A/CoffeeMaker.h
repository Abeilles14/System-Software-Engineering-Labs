#include "../../rt.h"

#ifndef   __CoffeeMaker__
#define   __CoffeeMaker__

class CoffeeMaker : public ActiveClass{
private:
	int main(void);

	int machineNumber;
	int currentState;
	bool start;

public:
	CoffeeMaker(int number);
};

#endif