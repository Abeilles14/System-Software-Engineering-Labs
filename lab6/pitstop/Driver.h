#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>
#include <vector>

class Driver : public ActiveClass
{
private:
	// Which driver
	int driverNumber;

	// How many laps to complete the race
	int lapNumber;

	// Amount of time taken per lap
	int laptime;

	// Contains number of laps in between pit stops
	int pitStopLaps;

	// Pit stop light controlled by supervisor. 
	CSemaphore* pitEntryLight;
	CSemaphore* pitStopLight;

	// Indicates whether or not the driver is in the pit stop.
	CSemaphore* driverInPitStop;

public:
	Driver(int pitstopNumber, int laps, int time, int pitstops) {
		// Same semaphore as one in pit stop
		this->pitEntryLight = new CSemaphore("pitEntryLight", 0);
		this->pitStopLight = new CSemaphore("pitStopLight", 0);
		this->driverInPitStop = new CSemaphore("driverInPitStop", 0);
		this->driverNumber = pitstopNumber;
		this->lapNumber = laps;
		this->laptime = time;
		this->pitStopLaps = pitstops;
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

			// Complete the race
			if (lap == this->lapNumber) {
				break;
			}

			// Check if the car needs a pitstop after a certain number of laps
			if (lap > lapsSincePitStop) {
				needPitStop = true;
				lapsSincePitStop += lapsSincePitStop;
			}

			// Check if the pitstop light is available
			// Will set pit stop light to zero as it consumes it
			if (pitEntryLight->Read() && needPitStop) {

				printf("Driver %d -> LAP: %d ENTERING PITSTOP.\n", this->driverNumber, this->lapNumber);

				// Wait for supervisor to signal driver to leave
				this->pitStopLight->Wait();
				printf("Driver %d -> LAP: %d EXITING PITSTOP.\n", this->driverNumber, this->lapNumber);
				needPitStop = false;
			}
		}

		return 0;
	}
};