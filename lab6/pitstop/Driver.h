#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>
#include <vector>

class Driver : public ActiveClass
{
private:
	int driverNumber;
	int lapNumber;

	std::vector<int> pitstopLaps;

public:
	Driver(int number, int laps, std::vector<int> pitstops, std::string driverMessage) {
		this->driverNumber = number;
		this->lapNumber = laps;

		this->pitstopLaps = pitstops;
	}

	~Driver() {}

	int main(void) {
		for (;;) {
			//TODO: check supervisor mutex for acess to pitstop

			printf("Driver %d -> LAP: %d ENTERING PITSTOP.\n", this->driverNumber, this->lapNumber);

			//TODO: threads doing some stuff

			printf("Driver %d -> LAP: %d EXITING PITSTOP.\n", this->driverNumber, this->lapNumber);
		
			//TODO: signal supervisor mutex to make resources available
		}

		return 0;
	}
};