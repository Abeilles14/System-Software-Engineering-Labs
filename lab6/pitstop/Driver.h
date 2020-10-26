#pragma once

#include "../../rt.h"
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
	std::vector<int> pitstopLaps;

	// Pit stop light controlled by supervisor. 
	CSemaphore* pitEntryLight;
	CSemaphore* pitExitLight;
public:
	Driver(int pitstopNumber, int laptime, std::vector<int> pitstops) {
		// Same semaphore as one in pit stop
		this->pitEntryLight = new CSemaphore("pitEntryLight", 0);
		this->pitExitLight = new CSemaphore("pitExitLight", 0);
		this->driverNumber = pitstopNumber;
		this->lapNumber = 0;
		this->laptime = laptime;
		this->pitstopLaps = pitstops;
	}

	int main(void) {
		int pitstopCount = 0;

		for (;;) {

			if (lapNumber == this->pitstopLaps[pitstopCount]) {
				printf("Driver %d -> LAP: %d REQUESTING ENTRY TO PITSTOP.\n", this->driverNumber, this->lapNumber);

				// Check if the pitstop light is available
				// Will set pit stop light to zero as it consumes it
				if (pitEntryLight->Wait(10) == WAIT_OBJECT_0) {

					printf("Driver %d -> LAP: %d ENTERING PITSTOP.\n", this->driverNumber, this->lapNumber);

					// Wait for supervisor to signal driver to leave
					this->pitExitLight->Wait();

					printf("Driver %d -> LAP: %d EXITING PITSTOP.\n", this->driverNumber, this->lapNumber);

					pitstopCount++;

				}
				else {		// if pitstop busy, start next lap, try again next lap
					printf("Driver %d -> LAP: %d DENIED ENTRY TO PITSTOP, TRY AGAIN NEXT LAP.\n", this->driverNumber, this->lapNumber);

					pitstopLaps[pitstopCount]++;
				}
			}
		}

		return 0;
	}
};