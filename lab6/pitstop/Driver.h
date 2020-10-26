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
	int laptime;

	std::vector<int> pitstopLaps;

	CSemaphore* pitStopLight;

public:
	Driver(int pitstopNumber, int number, int laps, int time, std::vector<int> pitstops) {
		this->putStopLight = new CSemaphore ("pitStopLight" + pitstopNumber, 1);
		this->driverNumber = number;
		this->lapNumber = laps;
		this->laptime = time;
		this->pitstopLaps = pitstops;
	}

	int main(void) {
	bool needPitStop = 0;
	int lap = 0;

	// Number of laps in between needed pit stops
	int lapsSincePitStop = 5;

		for (;;) {
			// Each lap increment
			Sleep(laptime);
			lap++;

			// Check if the car needs a pitstop after a certain number of laps
			if (lap > lapsSincePitStop) {
				needPitStop = true;
				lapsSincePitStop += lapsSincePitStop;
			}

			if (this->pitStopLight.Read() && needPitStop) {
				
				printf("Driver %d -> LAP: %d ENTERING PITSTOP.\n", this->driverNumber, this->lapNumber);
				pitStopLight.Signal();

				pitStopLight.Wait();
				printf("Driver %d -> LAP: %d EXITING PITSTOP.\n", this->driverNumber, this->lapNumber);
				needPitStop = false;
			}
		}

		return 0;
	}
};