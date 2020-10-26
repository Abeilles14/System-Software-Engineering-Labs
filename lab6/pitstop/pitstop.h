#pragma once

#include "../../rt.h"
#include "Technician.h"

#define NUMBER_OF_TECHNICIANS 17

class PitStop : public ActiveClass
{
private:
	CSemaphore* frontWheels;
	CSemaphore* backWheels;

	CSemaphore* jackingFront;
	CSemaphore* jackingBack;
	CSemaphore* visor;
	CSemaphore* debris;
	CSemaphore* refuel;
	CSemaphore* pitStopLight;
	CSemaphore* driverInPitStop;

	int pitstopNumber;

	UINT __stdcall Supervisor(void* args) {
		for (;;) {
			if (driverInPitStop.Read()) {

			}

		}

	}

public:
	PitStop(int pitstopNumber) {
		this->frontWheels = new CSemaphore("front" + pitstopNumber, 3);
		this->backWheels = new CSemaphore("back"  + pitstopNumber, 3);

		this->jackingFront = new CSemaphore("jackingFront" + pitstopNumber,1 );
		this->jackingBack = new CSemaphore("jackingBack" + pitstopNumber, 1);
		this->visor = new CSemaphore("visor" + pitstopNumber, 1);
		this->debris = new CSemaphore("debris" + pitstopNumber, 1);
		this->refuel = new CSemaphore("refuel" + pitstopNumber, 1);
		this->pitStopLight = new CSemaphore("pitStopLight" + pitstopNumber, 1);
		this->driverInPitStop = new CSemaphore("driverInPitStop" + pitstopNumber, 1);

		this->pitstopNumber = pitstopNumber;
	}

	~PitStop() {
		delete this->frontWheels;
		delete this->backWheels;

		delete this->jackingFront;
		delete this->jackingBack;
		delete this->visor;
		delete this->debris;
		delete this->refuel;
		delete this->pitStopLight;
	}

	int main(void) {
		Technician* jackingFront = new Technician("jackingFront" + pitstopNumber, 1, 2000, "Jacking (Front)", "Raising front", 0, pitstopNumber);
		Technician* jackingBack = new Technician("jackingBack" + pitstopNumber, 1, 2000, "Jacking (Front)", "Raising front", 0, pitstopNumber);

		Technician* nutFW = new Technician("front" + pitstopNumber, 1, 2000, "Wheel Tech (Front)", "Removing nut", 0, pitstopNumber);
		Technician* removeFW = new Technician("front" + pitstopNumber, 1, 2000, "Wheel Tech (Front)", "Removing wheel", 0, pitstopNumber);
		Technician* replaceFW = new Technician("front" + pitstopNumber, 1, 2000, "Wheel Tech (Front)", "Replacing wheel", 0, pitstopNumber);

		Technician* nutBK = new Technician("back" + pitstopNumber, 1, 2000, "Wheel Tech (Back)", "Removing nut", 0, pitstopNumber);
		Technician* removeBK = new Technician("back" + pitstopNumber, 1, 2000, "Wheel Tech (Back)", "Removing wheel", 0, pitstopNumber);
		Technician* replaceBK = new Technician("back" + pitstopNumber, 1, 2000, "Wheel Tech (Back)", "Replacing wheel", 0, pitstopNumber);

		Technician* visor = new Technician("visor" + pitstopNumber, 1, 2000, "Visor Tech", "Cleaning visor", 0, pitstopNumber);
		Technician* debris = new Technician("debris" + pitstopNumber, 1, 2000, "Debris Tech", "Cleaning debris", 0, pitstopNumber);
		Technician* refuel = new Technician("refuel" + pitstopNumber, 1, 2000, "Refuel Tech", "Refueling car", 0, pitstopNumber);

		CThread supervisor(this->Supervisor, ACTIVE, NULL);		// create the 3 other child threads

		supervisor.WaitForThread();

		return 0;
	}
};
