  
#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>

class Elevator : public ActiveClass
{
private:
	struct elevatorStatus {
		int currentFloor;
		std::string headingDirection;
		std::string doorStatus;
		bool outOfOrder;
	};

	int cursorX;

	CSemaphore* task;
	CMutex* monitorMutex;
	CMailbox* mailBox;

public:
	Elevator(std::string elevatorName, std::string monitorName, std::string mailBoxName) {
		this->task = new CSemaphore(elevatorName, 1);
		this->monitorMutex = new CMutex(monitorName, 1);
		this->mailBox = new CMailbox();
	}

	int main(void) {
		monitorMutex->Wait();
		MOVE_CURSOR(this->cursorX, 1);
		printf("0");
		fflush(stdout);
		monitorMutex->Signal();
		for (;;) {
			this->task->Wait();

			// Setup timing
			monitorMutex->Wait();
			MOVE_CURSOR(this->cursorX, 1);
			printf("1");
			fflush(stdout);
			monitorMutex->Signal();
			SLEEP(taskTime);

			monitorMutex->Wait();
			MOVE_CURSOR(this->cursorX, 1);
			printf("0");
			fflush(stdout);
			monitorMutex->Signal();

			this->task->Signal();
			Sleep(5000);
		}

		return 0;
	}
};