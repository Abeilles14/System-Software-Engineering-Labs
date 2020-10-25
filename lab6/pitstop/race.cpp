#include "../../rt.h"
#include "Technician.h"
#include "Driver.h"
#include "pitstop.h"
#include <new.h>


#define NUMBER_OF_PITSTOPS 10

CSemaphore nutRemovedFront("nutRemovedFront", 1);
CSemaphore oldWheelFront("oldWheelFront", 1);
CSemaphore newWheelFront("newWheelFront", 1);
CSemaphore nutRemovedBack("nutRemovedBack", 1);;
CSemaphore oldWheelBack("oldWheelBack", 1);;
CSemaphore newWheelback("newWheelback", 1);;

CSemaphore jackingFront("jackingFront", 1);
CSemaphore jackingBack("jackingBack", 1);
CSemaphore visor("visor", 1);
CSemaphore debris("debris", 1);
CSemaphore refuel("refuel", 1);
CSemaphore pitEntryLight("pitEntryLight", 1);
CSemaphore pitStopLight("pitStopLight", 1);

CSemaphore driverInPitStop("driverInPitStop", 0);

UINT __stdcall Supervisor(void* args) {
	// Wait for all mutexes to be available
	bool front = 0;
	bool back = 0;
	bool frontNut = 0;
	bool frontOldWheel = 0;
	bool frontNewWheel = 0;
	bool backNut = 0;
	bool backOldWheel = 0;
	bool backNewWheel = 0;

	for (;;) {

		newWheelFront.Wait(10);
		nutRemovedBack.Wait(10);
		oldWheelBack.Wait(10);
		newWheelback.Wait(10);

		if (jackingFront.Wait(10) == WAIT_OBJECT_0 && front) {
			nutRemovedFront.Signal();
			front = 0;
			frontNut = 1;
			Sleep(100);
		}

		if (nutRemovedFront.Wait(10) == WAIT_OBJECT_0 && frontNut) {
			oldWheelFront.Signal();
			frontNut = 0;
			frontOldWheel = 1;
			Sleep(100);
		}

		if (oldWheelFront.Wait(10) == WAIT_OBJECT_0 && frontOldWheel) {
			newWheelFront.Signal();
			frontOldWheel = 0;
			frontNewWheel = 1;
			Sleep(100);
		}


		jackingBack.Wait(10);
		visor.Wait(10);
		debris.Wait(10);
		refuel.Wait(10);
		// Wait for technicians to be available again
		// Wait will decrement all of the resources, making them zero.

		// IF RANDOM CONDITION
		// Consume pit entry light
		if (pitEntryLight.Wait(0) == WAIT_OBJECT_0) {
			// Refueling, visor, and debris technicians begin work
			visor.Signal();
			debris.Signal();
			refuel.Signal();

			jackingFront.Signal();
			front = 1;
			jackingBack.Signal();
			back = 1;

		}




	}

}

int main()
{
	CThread supervisorThread(Supervisor, ACTIVE, NULL);

	Technician jackingFront("jackingFront", 1, 2000, "Jacking (Front)", "Raising front", 0);
	Technician jackingBack("jackingBack", 1, 2000, "Jacking (Front)", "Raising front", 0);

	Technician nutFW("nutRemovedFront", 1, 2000, "Wheel Tech (Front)", "Removing nut", 0);
	Technician removeFW("oldWheelFront", 1, 2000, "Wheel Tech (Front)", "Removing wheel", 0);
	Technician replaceFW("newWheelFront", 1, 2000, "Wheel Tech (Front)", "Replacing wheel", 0);

	Technician nutBK("back", 1, 2000, "Wheel Tech (Back)", "Removing nut", 0);
	Technician removeBK("back", 1, 2000, "Wheel Tech (Back)", "Removing wheel", 0);
	Technician replaceBK("back", 1, 2000, "Wheel Tech (Back)", "Replacing wheel", 0);

	Technician visor("visor", 1, 2000, "Visor Tech", "Cleaning visor", 0);
	Technician debris("debris", 1, 2000, "Debris Tech", "Cleaning debris", 0);
	Technician refuel("refuel", 1, 2000, "Refuel Tech", "Refueling car", 0);

	jackingFront.Resume();
	jackingBack.Resume();

	nutFW.Resume();
	removeFW.Resume();
	replaceFW.Resume();

	nutBK.Resume();
	removeBK.Resume();
	replaceBK.Resume();

	visor.Resume();
	debris.Resume();
	refuel.Resume();

	for (;;) {

	}



	return 0;
}