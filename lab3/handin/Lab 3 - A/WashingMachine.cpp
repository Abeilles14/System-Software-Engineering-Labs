#include "../../rt.h"
#include "WashingMachine.h"

#define IDLE 0
#define FILLING 1
#define WASHING 2
#define DRAINING 3
#define SPINNING 4
#define END 5

WashingMachine::WashingMachine(int number) {
	this->machineNumber = number;
	this->currentState = IDLE;
	this->start = false;
}

int WashingMachine::main(void) {
	printf("Washing Machine %d: Ready\n", this->machineNumber);

	while(start) {
		switch (this->currentState) {
			case IDLE: {
				printf("Washing Machine %d: idling\n", this->machineNumber);
				this->currentState = IDLE;
				Sleep(3000);
				break;
			}
			case FILLING: {
				printf("Washing Machine %d: filling\n", this->machineNumber);
				this->currentState = WASHING;
				Sleep(3000);
				break;
			}
			case WASHING: {
				printf("Washing Machine %d: washing\n", this->machineNumber);
				this->currentState = DRAINING;
				Sleep(3000);
				break;
			}
			case DRAINING: {
				printf("Washing Machine %d: draining\n", this->machineNumber);
				this->currentState = SPINNING;
				Sleep(3000);
				break;
			}
			case SPINNING: {
				printf("Washing Machine %d: spinning\n", this->machineNumber);
				this->currentState = END;
				Sleep(3000);
				break;
			}
			case END: {
				printf("Washing Machine %d: finished. Closing thread\n", this->machineNumber);
				return 0;
			}
		}
	}
}