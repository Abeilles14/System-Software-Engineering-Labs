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

public:
	Technician(std::string mutexName, int resources, int taskTime, std::string role, std::string taskMessage, int cursorX) {
		this->task = new CSemaphore(mutexName, 0);
		this->taskTime = taskTime;
		this->role = role;
		this->message = taskMessage;
		this->cursorX = cursorX;
		this->pitstopNum = pitstopNum;
	}

	int main(void) {
		for (;;) {
			this->task->Wait();

			printf("TECH: %s -> TASK: %s BEGINNING.\n", this->role.c_str(), this->message.c_str());

			// Setup timing
			SLEEP(taskTime);

			printf("TECH: %s -> TASK: %s COMPLETED.\n", this->role.c_str(), this->message.c_str());

			this->task->Signal();
			Sleep(2000);
		}

		return 0;
	}
};