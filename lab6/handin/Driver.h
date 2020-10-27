#pragma once

#include "../../rt.h"
#include <vector>

#define NUMBER_OF_LAPS 20

class Driver : public ActiveClass
{
private:
	// Which driver
	int driverNumber;

	// Amount of time taken per lap
	int laptime;

	// Contains number of laps in between pit stops
	std::vector<int> pitstopLaps;

	// Pit stop light controlled by supervisor. 
	CSemaphore* pitEntryLight;
	CSemaphore* pitExitLight;

	CMutex* monitorMutex;

public:
	Driver(int pitstopNumber, int laptime, std::vector<int> pitstops) {
		// Same semaphore as one in pit stop
		this->pitEntryLight = new CSemaphore("pitEntryLight", 0);
		this->pitExitLight = new CSemaphore("pitExitLight", 0);
		this->driverNumber = pitstopNumber;
		this->laptime = laptime;
		this->pitstopLaps = pitstops;
		this->monitorMutex = new CMutex("Monitor", 1);
	}

	int main(void) {
		int pitstopCount = 0;

		for (int lapNumber = 0; lapNumber < NUMBER_OF_LAPS; lapNumber++) {
			if (lapNumber == this->pitstopLaps[pitstopCount]) {
				monitorMutex->Wait();
				MOVE_CURSOR(0, 20);
				printf("%c[2K", 27);
				printf("Driver %d -> LAP: %d REQUESTING ENTRY TO PITSTOP.\n", this->driverNumber, lapNumber);
				fflush(stdout);
				monitorMutex->Signal();

				// Check if the pitstop light is available
				// Will set pit stop light to zero as it consumes it
				if (pitEntryLight->Wait(10) == WAIT_OBJECT_0) {
					monitorMutex->Wait();
					MOVE_CURSOR(0, 21);
					printf("%c[2K", 27);
					printf("Driver %d -> LAP: %d ENTERING PITSTOP.\n", this->driverNumber, lapNumber);
					fflush(stdout);
					monitorMutex->Signal();

					// Wait for supervisor to signal driver to leave
					this->pitExitLight->Wait();

					monitorMutex->Wait();
					MOVE_CURSOR(0, 22);
					printf("%c[2K", 27);
					printf("Driver %d -> LAP: %d EXITING PITSTOP.\n", this->driverNumber, lapNumber);
					fflush(stdout);
					monitorMutex->Signal();

					if (pitstopLaps[pitstopCount] != pitstopLaps[pitstopLaps.size() - 1]) {
						pitstopCount++;
					}

				}
				else {		// if pitstop busy, start next lap, try again next lap
					monitorMutex->Wait();
					MOVE_CURSOR(0, 23);
					printf("%c[2K", 27);
					printf("Driver %d -> LAP: %d DENIED ENTRY TO PITSTOP, TRY AGAIN NEXT LAP.\n", this->driverNumber, lapNumber);
					fflush(stdout);
					monitorMutex->Signal();

					pitstopLaps[pitstopCount]++;
				}

			}

			monitorMutex->Wait();
			MOVE_CURSOR(3, driverNumber + 3);
			printf("%d      %d\n", this->driverNumber, lapNumber + 1);
			fflush(stdout);
			monitorMutex->Signal();

			Sleep(laptime);
		}

		monitorMutex->Wait();
		MOVE_CURSOR(18, driverNumber + 3);
		printf("Driver %d -> HAS FINISHED THE RACE, CONGRATULATIONS! :)\n", this->driverNumber);
		fflush(stdout);
		monitorMutex->Signal();

		return 0;
	}
};