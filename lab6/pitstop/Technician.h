#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>

class Technician : public ActiveClass
{
private:
	int taskTime;
	int cursorX;
	int pitstopNum;

	std::string role;
	std::string message;

	CSemaphore* task;
	CMutex* monitorMutex;

public:
	Technician(std::string mutexName, int taskTime, int cursorX, int resources) {
		this->task = new CSemaphore(mutexName, 0, resources);
		this->taskTime = taskTime;
		this->role = role;
		this->cursorX = cursorX;
		this->pitstopNum = pitstopNum;
		this->monitorMutex = new CMutex("Monitor", 1);
	}

	int main(void) {
		monitorMutex->Wait();
		MOVE_CURSOR(this->cursorX, 1);
		printf("0");
		fflush(stdout);
		monitorMutex->Signal();
		for (;;) {
			this->task->Wait();

			//printf("TECH: %s -> TASK: %s BEGINNING.\n", this->role.c_str(), this->message.c_str());

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
