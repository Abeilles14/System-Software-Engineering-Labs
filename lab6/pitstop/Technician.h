#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>

class Technician : public ActiveClass
{
private:
	int technicianNumber;
	time_t taskTime;
	std::string message;

	CMutex* sharedMutex;

public:
	Technician(std::string mutexName, int number, time_t taskTime, std::string taskMessage) {
		this->sharedMutex = new CMutex("__MonitorMutex__" + mutexName);
		this->technicianNumber = number;
		this->taskTime = taskTime;
		this->message = taskMessage;
	}

	~Technician() {
		delete this->sharedMutex;
		cout << "Mutex deleted";
	}

	int main(void) {
		for (;;) {
			this->sharedMutex->Wait();

			printf("Technician %d -> TASK: %s BEGINNING.\n", this->technicianNumber, this->message.c_str());

			// Setup timing
			auto finishTime = time(0) + this->taskTime;

			for(;;) {
				if (finishTime < time(0)) {
					break;
				}
			}

			printf("Technician %d -> TASK: %s COMPLETED.\n", this->technicianNumber, this->message.c_str());

			this->sharedMutex->Signal();
		}

	return 0;
	}
};