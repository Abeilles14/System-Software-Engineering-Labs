#include "../../rt.h"
#include "CoffeeMaker.h"

#define IDLE 0
#define HEATING 1
#define BREWING 2
#define SERVING 3
#define COOLING 4
#define END 5

#define GRINDING 6
#define FILTERING 7
#define DISPENSING 8

CoffeeMaker::CoffeeMaker(int number) {
	this->machineNumber = number;
	this->currentState = IDLE;
	this->start = false;
	this->running = true;
}

void CoffeeMaker::Start() {
	printf("Coffee Maker %d started\n", this->machineNumber);
	this->start = true;
}

void CoffeeMaker::Stop() {
	printf("Coffee Maker %d stopped\n", this->machineNumber);
	this->start = false;
}

void CoffeeMaker::End() {
	this->running = false;
}

int CoffeeMaker::main(void) {
	printf("Coffee Maker %d: Ready\n", this->machineNumber);

	CThread t1(this->GrindCoffee, SUSPENDED, NULL);
	CThread t2(this->AddMilkCream, SUSPENDED, NULL);

	for (;;) {
		if (start) {
			switch (this->currentState) {
				case IDLE: {
					printf("Coffee Maker %d idling\n", this->machineNumber);
					Sleep(2000);
					this->currentState = HEATING;
					break;
				}
				case HEATING: {
					printf("Coffee Maker %d heating\n", this->machineNumber);
					Sleep(2000);
					this->currentState = BREWING;
					break;
				}
				case BREWING: {
					printf("Coffee Maker %d brewing\n", this->machineNumber);
					t1.Resume();
					Sleep(2000);
					t1.WaitForThread();
					this->currentState = SERVING;
					break;
				}
				case SERVING: {
					printf("Coffee Maker %d serving\n", this->machineNumber);
					t2.Resume();
					Sleep(2000);
					t2.WaitForThread();
					this->currentState = COOLING;
					break;
				}
				case COOLING: {
					printf("Coffee Maker %d cooling\n", this->machineNumber);
					Sleep(2000);
					this->currentState = END;
					break;
				}
				case END: {
					printf("Coffee Maker %d finished. Turning off\n", this->machineNumber);
					this->currentState = IDLE;
					this->start = false;
				}
			}
		}
		if (!running) {
			printf("Washing Machine %d: turning off\n", this->machineNumber);
			return 0;
		}
	}

	return 0;
}

UINT __stdcall CoffeeMaker::GrindCoffee(void* args) {
	UINT grindingState = IDLE;

	for (;;) {
		switch (grindingState) {
			case IDLE: {
				printf("Coffee Maker %d: coffee grinding idling\n", this->machineNumber);
				Sleep(1000);
				grindingState = GRINDING;
				break;
			}
			case GRINDING: {
				printf("Coffee Maker %d: coffee grinding running\n", this->machineNumber);
				Sleep(2000);
				grindingState = FILTERING;
				break;
			}
			case FILTERING: {
				printf("Coffee Maker %d: grinded coffee filtering\n", this->machineNumber);
				Sleep(3000);
				grindingState = IDLE;
				return 0;
			}
		}
	}

	return 0;
}

UINT __stdcall CoffeeMaker::AddMilkCream(void* args) {
	UINT milkCreamState = IDLE;

	for (;;) {
		switch (milkCreamState) {
			case IDLE: {
				printf("Coffee Maker %d: coffee milk and cream idling\n", this->machineNumber);
				Sleep(1000);
				milkCreamState = DISPENSING;
				break;
			}
			case DISPENSING: {
				printf("Coffee Maker %d: coffee milk and cream dispensing\n", this->machineNumber);
				Sleep(2000);
				milkCreamState = IDLE;
				return 0;
			}
		}
	}

	return 0;
}


