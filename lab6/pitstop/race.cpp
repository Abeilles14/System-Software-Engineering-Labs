#include "../../rt.h"
#include "Technician.h"
#include "Driver.h"
#include "pitstop.h"
#include <new.h>


#define NUMBER_OF_PITSTOPS 10
#define NUMBER_OF_LAPS 20

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
CSemaphore pitExitLight("pitExitLight", 1);

CMutex monitorMutex("Monitor", 1);

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
	bool frontComplete = 0;
	bool backComplete = 0;

	for (;;) {
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

		if (newWheelFront.Wait(10) == WAIT_OBJECT_0 && frontNewWheel) {
			jackingFront.Signal();
			frontNewWheel = 0;
			backComplete = 1;
		}

		if (jackingBack.Wait(10) == WAIT_OBJECT_0 && back) {
			nutRemovedBack.Signal();
			back = 0;
			backNut = 1;
			Sleep(100);
		}

		if (nutRemovedBack.Wait(10) == WAIT_OBJECT_0 && backNut) {
			oldWheelBack.Signal();
			backNut = 0;
			backOldWheel = 1;
			Sleep(100);
		}

		if (oldWheelBack.Wait(10) == WAIT_OBJECT_0 && backOldWheel) {
			newWheelback.Signal();
			backOldWheel = 0;
			backNewWheel = 1;
			Sleep(100);
		}

		if (newWheelback.Wait(10) == WAIT_OBJECT_0 && backNewWheel) {
			jackingBack.Signal();
			backNewWheel = 0;
			backComplete = 1;
		}

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

		if (frontComplete && backComplete) {
			pitExitLight.Signal();
		}

	}
}

int main()
{
	std::string pitList = "Pit_Entry_Light Pit_Exit_Light Refuel Visor Debris (front - back) Jacking Wheel_Nut Old_Wheel New_Wheel";

	CThread supervisorThread(Supervisor, ACTIVE, NULL);

	Technician jackingFront("jackingFront", 2000, pitList.find("Jacking"));
	Technician jackingBack("jackingBack", 2000, pitList.find("Jacking") + 4);

	Technician nutFW("nutRemovedFront", 2000, pitList.find("Wheel_Nut"));
	Technician removeFW("oldWheelFront", 2000, pitList.find("Old_Wheel"));
	Technician replaceFW("newWheelFront", 2000, pitList.find("New_Wheel"));

	Technician nutBK("nutRemovedBack", 2000, pitList.find("Wheel_Nut") + 4);
	Technician removeBK("oldWheelBack", 2000, pitList.find("Old_Wheel") + 4);
	Technician replaceBK("newWheelBack", 2000, pitList.find("New_Wheel") + 4);

	Technician visor("visor", 2000, pitList.find("Visor"));
	Technician debris("debris", 2000, pitList.find("Debris"));
	Technician refuel("refuel", 2000, pitList.find("Refuel"));

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
		Driver one(1, 1000, { 1, 10 });
		Driver two(2, 300, { 2, 11 });
		Driver three(3, 500, { 5, 15 });
		Driver four(4, 200, { 8, 10, 20 });
		Driver five(5, 1000, { 10, 14, 18 });
		Driver six(6, 500, { 12, 15, 19 });
		Driver seven(7, 300, { 2, 7 });
		Driver eight(8, 1000, { 6, 9 });
		Driver nine(9, 300, { 9, 13 });
		Driver ten(10, 400, { 11, 17 });

		monitorMutex.Wait();
		MOVE_CURSOR(0, 0);
		printf(pitList.c_str());


		// Pit entry light
		MOVE_CURSOR(0, 1);
		printf("%d", pitEntryLight.Read() == true);
		MOVE_CURSOR(0, 1);
		printf("%d", pitExitLight.Read() == true);

		MOVE_CURSOR(0, 2);
		printf("Car Lap In_Pit_Stop");
		fflush(stdout);
		monitorMutex.Signal();
	}

	return 0;
}