#include "../../rt.h"
#include "Technician.h"
#include "Driver.h"
#include <new.h>
#include <windows.h>

#define NUMBER_OF_PITSTOPS 10
#define NUMBER_OF_LAPS 20

CSemaphore nutRemovedFront("nutRemovedFront", 1);
CSemaphore oldWheelFront("oldWheelFront", 1);
CSemaphore newWheelFront("newWheelFront", 1);
CSemaphore nutRemovedBack("nutRemovedBack", 1);
CSemaphore oldWheelBack("oldWheelBack", 1);
CSemaphore newWheelback("newWheelback", 1);

CSemaphore jackingFront("jackingFront", 1);
CSemaphore jackingBack("jackingBack", 1);
CSemaphore visor("visor", 1);
CSemaphore debris("debris", 1);
CSemaphore refuel("refuel", 1);

CSemaphore pitEntryLight("pitEntryLight", 1);
CSemaphore pitExitLight("pitExitLight", 0);

CMutex monitorMutex("Monitor", 1);

void printCar();
void printRaceCar();

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
	bool busy = 0;

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
			frontComplete = 1;
			Sleep(200);
		}

		if (jackingBack.Wait(10) == WAIT_OBJECT_0 && back) {
			nutRemovedBack.Signal();
			back = 0;
			backNut = 1;
			Sleep(200);
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
			Sleep(100);
		}

		visor.Wait(10);
		debris.Wait(10);
		refuel.Wait(10);
		// Wait for technicians to be available again
		// Wait will decrement all of the resources, making them zero.

		// Consume pit entry light
		if (pitEntryLight.Read() == 0 && !busy) {
			busy = 1;
			Sleep(400);
			// Refueling, visor, and debris technicians begin work
			visor.Signal();
			debris.Signal();
			refuel.Signal();

			jackingFront.Signal();
			front = 1;
			jackingBack.Signal();
			back = 1;
			Sleep(400);
		}

		if (frontComplete && backComplete) {
			pitExitLight.Signal();
			Sleep(20);
			pitEntryLight.Signal();
			Sleep(20);
			busy = 0;
			backComplete = 0;
			frontComplete = 0;
		}


		monitorMutex.Wait();
		MOVE_CURSOR(3, 1);
		printf("%d", busy);
		MOVE_CURSOR(23, 1);
		printf("%d", !busy);
		monitorMutex.Signal();
	}
}

int main()
{
	HWND console = GetConsoleWindow();
	RECT rect;
	GetWindowRect(console, &rect);
	MoveWindow(console, rect.left, rect.top - 50, 1200, 700, TRUE);

	std::string pitList = "|| Pit_Entry_Light  || Pit_Exit_Light || Refuel || Visor || Debris || Jacking(F)(B) || Wheel_Nut(F)(B) || Old_Wheel(F)(B) || New_Wheel(F)(B) ||";
	CThread supervisorThread(Supervisor, ACTIVE, NULL);

	Technician jackingFront("jackingFront", 1000, pitList.find("Jacking") + 8);
	Technician jackingBack("jackingBack", 1000, pitList.find("Jacking") + 11);

	Technician nutFW("nutRemovedFront", 2000, pitList.find("Wheel_Nut") + 10);
	Technician removeFW("oldWheelFront", 1000, pitList.find("Old_Wheel") + 10);
	Technician replaceFW("newWheelFront", 3000, pitList.find("New_Wheel") + 10);

	Technician nutBK("nutRemovedBack", 2000, pitList.find("Wheel_Nut") + 13);
	Technician removeBK("oldWheelBack", 1000, pitList.find("Old_Wheel") + 13);
	Technician replaceBK("newWheelBack", 3000, pitList.find("New_Wheel") + 13);

	Technician visor("visor", 1000, pitList.find("Visor"));
	Technician debris("debris", 2000, pitList.find("Debris"));
	Technician refuel("refuel", 3000, pitList.find("Refuel"));

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

	Driver one(1, 1000, { 1, 10 });
	Driver two(2, 1100, { 2, 11 });
	Driver three(3, 900, { 5, 15 });
	Driver four(4, 1200, { 8, 10, 20 });
	Driver five(5, 1100, { 10, 14, 18 });
	Driver six(6, 900, { 12, 15, 19 });
	Driver seven(7, 1000, { 2, 7 });
	Driver eight(8, 1020, { 6, 9 });
	Driver nine(9, 1030, { 9, 13 });
	Driver ten(10, 1040, { 11, 17 });

	one.Resume();
	two.Resume();
	three.Resume();
	four.Resume();
	five.Resume();
	six.Resume();
	seven.Resume();
	eight.Resume();
	nine.Resume();
	ten.Resume();

	monitorMutex.Wait();
	MOVE_CURSOR(0, 0);
	printf(pitList.c_str());
	MOVE_CURSOR(0, 3);
	printf("|| Car || Lap || In_Pit_Stop ||");
	monitorMutex.Signal();

	//printCar();
	printRaceCar();

	one.WaitForThread();
	two.WaitForThread();
	three.WaitForThread();
	four.WaitForThread();
	five.WaitForThread();
	six.WaitForThread();
	seven.WaitForThread();
	eight.WaitForThread();
	nine.WaitForThread();
	ten.WaitForThread();

	return 0;
}

void printRaceCar() {
	monitorMutex.Wait();
	MOVE_CURSOR(0, 24);

	cout << endl << "(1): indicates technician is working." << endl;
	cout << "(0): indicates technician is free." << endl;

	cout << "                                        _.....____......._____.._                                        " << endl;
	cout << "                                  _..--'    || ======\\ \\========== `-._                                   " << endl;
	cout << "                         ______.-''         ||        \\ \\             \\ \\`-. _                             " << endl;
	cout << "                        /_      \\ \\_________||_________\\ \\_____________\\ \\____''_-..__                    " << endl;
	cout << "     _.-. _             00|      _.----._              |               |          _.._`--. _             " << endl;
	cout << "  _.(    ) ),--.        00|    .'+..--..+`.   ~ ~ ~ ~  | ~ ~ ~ ~ ~ ~ ~ | ~ ~ ~ .'.---..`.    '-._        " << endl;
	cout << "(               )-._    \\0|   /++/  __  \\++\\  ~ ~ ~ ~  | (^^^) ~ ~ ~ ~ | ~ ~  /+/  __  \\+\\       0033    " << endl;
	cout << " ( _________________)     |  |++|  /  \\  |++|          |               |     /+|  /  \\  |+|       \\003   " << endl;
	cout << "                           \\_|++|  \\__/  |++|__________|_______________|_____|+|  \\__/  |+|__________3   " << endl;
	cout << "     VROOM VROOM            \\W\\++\\      /++/W_W_W_W_W_W_W_W_W_W_W_W_W_W_W_W_W_\\+\\      /+/_W_W_W_W_W/    " << endl;
	cout << "                                \\+`===='+/                                     `+`===='+'                " << endl;
	cout << "                       ===============================================================================" << endl;
	
	monitorMutex.Signal();
}

void printCar() {
	monitorMutex.Wait();
	MOVE_CURSOR(0, 26);

	cout << "           _________        " << endl;
	cout << "          / /  || \\ \\       " << endl;
	cout << "      ___/ /___||__\\ \\____  " << endl;
	cout << "= =  /  _          _     () " << endl;
	cout << "= =  \\_/ \\________/ \\____/  " << endl;
	cout << "_______\\_/________\\_/_________ " << endl;

	cout << endl << "(1): indicates technician is working." << endl;
	cout << "(0): indicates technician is free.";
	monitorMutex.Signal();
}