#include "../../rt.h"
#include "WashingMachine.h"

#define UINT unsigned int
#define IDLE 0
#define FILLING 1
#define WASHING 2
#define DRAINING 3
#define SPINNING 4
#define END 5

#define RUNNING 6
#define STOPPING 7

UINT __stdcall WaterInletValve(void* args);
UINT __stdcall Motor(void* args);

WashingMachine::WashingMachine(int number) {
	this->machineNumber = number;
	this->currentState = IDLE;
	this->start = false;
	this->running = true;
}

void WashingMachine::Start() {
	printf("Washing Machine %d started\n", this->machineNumber);
	this->start = true;
}

void WashingMachine::Stop() {
	printf("Washing Machine %d stopped\n", this->machineNumber);
	this->start = false;
}

void WashingMachine::End() {
	this->running = false;
}

int WashingMachine::main(void) {
	printf("Washing Machine %d: Ready\n", this->machineNumber);

	CThread t1(Motor, SUSPENDED, &this->machineNumber);
	CThread t2(WaterInletValve, SUSPENDED, &this->machineNumber);

	for (;;) {
		if (start) {
			switch (this->currentState) {
				case IDLE: {
					printf("Washing Machine %d: idling\n", this->machineNumber);
					this->currentState = FILLING;
					Sleep(2000);
					break;
				}
				case FILLING: {
					printf("Washing Machine %d: filling\n", this->machineNumber);
					t2.Resume();
					t2.WaitForThread();
					this->currentState = WASHING;
					Sleep(2000);
					break;
				}
				case WASHING: {
					printf("Washing Machine %d: washing\n", this->machineNumber);
					t1.Resume();
					this->currentState = DRAINING;
					Sleep(2000);
					break;
				}
				case DRAINING: {
					printf("Washing Machine %d: draining\n", this->machineNumber);
					this->currentState = SPINNING;
					Sleep(2000);
					break;
				}
				case SPINNING: {
					printf("Washing Machine %d: spinning\n", this->machineNumber);
					this->currentState = END;
					Sleep(2000);
					break;
				}
				case END: {
					printf("Washing Machine %d: finished. Going back to idle\n", this->machineNumber);
					t1.WaitForThread();
					this->currentState = IDLE;
					this->start = false;
				}
			}
		}
		if (!this->running) {
			printf("Washing Machine %d: turning off\n", this->machineNumber);
			return 0;
		}
	}
	return 0;
}

UINT __stdcall WaterInletValve(void* args) {
	int machineNumber = *(int*)(args);

	UINT inletValveState = IDLE;

	for (;;) {
		switch (inletValveState) {
			case IDLE: {
				printf("Washing Machine %d: inlet valve starting\n", machineNumber);
				inletValveState = FILLING;
				Sleep(2000);
				break;
			}
			case FILLING: {
				printf("Washing Machine %d: inlet valve filling\n", machineNumber);
				inletValveState = STOPPING;
				Sleep(2000);
				break;
			}
			case STOPPING: {
				printf("Washing Machine %d: inlet valve stopping\n", machineNumber);
				Sleep(2000);
				return 0;
			}
		}
	}

	return 0;
}

UINT __stdcall Motor (void* args) {
	int machineNumber = *(int*)(args);

	UINT motorState = IDLE;

	for (;;) {
		switch(motorState) {
			case IDLE: {
				printf("Washing Machine %d: motor idling\n", machineNumber);
				motorState = RUNNING;
				Sleep(2000);
				break;
			}
			case RUNNING: {
				printf("Washing Machine %d: motor running\n", machineNumber);
				motorState = STOPPING;
				Sleep(5000);
				break;
			}
			case STOPPING: {
				printf("Washing Machine %d: motor stopping\n", machineNumber);
				Sleep(2000);
				return 0;
			}
		}
	}
}