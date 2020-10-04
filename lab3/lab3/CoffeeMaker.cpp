#include "../../rt.h"
#include "CoffeeMaker.h"

#define IDLE 0
#define HEATING 1
#define BREWING 2
#define SERVING 3
#define COOLING 4
#define END 5

CoffeeMaker::CoffeeMaker(int number) {
	this->machineNumber = number;
	this->currentState = IDLE;
	this->start = FALSE;
}

int CoffeeMaker::main(void) {
	printf("Coffee Maker %d: Ready\n", this->machineNumber);

	while(start) {
		switch (this->currentState) {
			case IDLE: {
				printf("Coffee Maker %d idling\n", this->machineNumber);
				Sleep(3000);
				this->currentState = IDLE;
				break;
			}
			case HEATING: {
				printf("Coffee Maker %d heating\n", this->machineNumber);
				Sleep(3000);
				this->currentState = BREWING;
				break;
			}
			case BREWING: {
				printf("Coffee Maker %d brewing\n", this->machineNumber);
				Sleep(3000);
				this->currentState = SERVING;
				break;
			}
			case SERVING: {
				printf("Coffee Maker %d serving\n", this->machineNumber);
				Sleep(3000);
				this->currentState = COOLING;
				break;
			}
			case COOLING: {
				printf("Coffee Maker %d cooling\n", this->machineNumber);
				Sleep(3000);
				this->currentState = END;
				break;
			}
			case END: {
				printf("Coffee Maker %d finished. Closing thread\n", this->machineNumber);
				return 0;
			}
		}
	}
}

