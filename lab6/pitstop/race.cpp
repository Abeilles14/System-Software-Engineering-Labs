#include "../../rt.h"
#include "Technician.h"
#include "Driver.h"
#include <new.h>
#include <windows.h>

#define NUMBER_OF_PITSTOPS 10
#define NUMBER_OF_LAPS 20

CSemaphore nutRemovedFront("nutRemovedFront", 1, 2);
CSemaphore oldWheelFront("oldWheelFront", 1, 2);
CSemaphore newWheelFront("newWheelFront", 1, 2);
CSemaphore nutRemovedBack("nutRemovedBack", 1, 2);
CSemaphore oldWheelBack("oldWheelBack", 1, 2);
CSemaphore newWheelBack("newWheelBack", 1, 2);

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
	int frontNut = 0;
	int frontOldWheel = 0;
	int frontNewWheel = 0;
	int backNut = 0;
	int backOldWheel = 0;
	int backNewWheel = 0;
	bool frontComplete = 0;
	bool backComplete = 0;
	bool busy = 0;

	for (;;) {
		if (jackingFront.Wait(10) == WAIT_TIMEOUT) {

		}
		else if (front) {
			nutRemovedFront.Signal(2);
			front = 0;
			frontNut = 2;
			Sleep(200);
		}

		if (nutRemovedFront.Wait(10) == WAIT_TIMEOUT) {

		}
		else if (frontNut) {
			oldWheelFront.Signal();
			frontNut--;
			frontOldWheel++;
			Sleep(200);
		}

		if (oldWheelFront.Wait(10) == WAIT_TIMEOUT) {

		}
		else if (frontOldWheel) {
			newWheelFront.Signal();
			frontOldWheel--;
			frontNewWheel++;
			Sleep(200);
		}

		if (newWheelFront.Wait(10) == WAIT_TIMEOUT) {

		}
		else if (frontNewWheel == 2) {
			jackingFront.Signal();
			frontNewWheel = 0;
			frontComplete = 1;
			Sleep(200);
		}

		if (jackingBack.Wait(10) == WAIT_TIMEOUT) {

		}
		else if (back) {
			nutRemovedBack.Signal(2);
			back = 0;
			backNut = 2;
			Sleep(200);
		}

		if (nutRemovedBack.Wait(10) == WAIT_TIMEOUT) {
		}
		else if (backNut) {
			oldWheelBack.Signal();
			backNut--;
			backOldWheel++;
			Sleep(200);
		}

		if (oldWheelBack.Wait(10) == WAIT_TIMEOUT) {
		}
		else if (backOldWheel) {
			newWheelBack.Signal();
			backOldWheel--;
			backNewWheel++;
			Sleep(200);
		}

		if (newWheelBack.Wait(10) == WAIT_TIMEOUT) {

		}
		else if (backNewWheel == 2) {
			jackingBack.Signal();
			backNewWheel = 0;
			backComplete = 1;
			Sleep(200);
		}

		visor.Wait(10);
		Sleep(10);
		debris.Wait(10);
		Sleep(10);
		refuel.Wait(10);
		Sleep(10);
		// Wait for technicians to be available again
		// Wait will decrement all of the resources, making them zero.

		// Consume pit entry light
		if (pitEntryLight.Read() == 0 && !busy) {
			busy = 1;
			Sleep(100);
			// Refueling, visor, and debris technicians begin work
			visor.Signal();
			Sleep(10);
			debris.Signal();
			Sleep(10);
			refuel.Signal();
			Sleep(10);
			jackingFront.Signal();
			Sleep(10);
			front = 1;
			jackingBack.Signal();
			Sleep(10);
			back = 1;
			Sleep(100);
		}

		if (frontComplete && backComplete) {
			pitExitLight.Signal();
			Sleep(100);
			pitEntryLight.Signal();
			Sleep(100);
			busy = 0;
			backComplete = 0;
			frontComplete = 0;
			Sleep(100);
		}


		monitorMutex.Wait();
		MOVE_CURSOR(3, 1);
		printf("%d", busy);
		MOVE_CURSOR(23, 1);
		printf("%d", !busy);
		monitorMutex.Signal();
		Sleep(100);
	}
}

int main()
{
	HWND console = GetConsoleWindow();
	RECT rect;
	GetWindowRect(console, &rect);
	MoveWindow(console, rect.left, rect.top, 1400, 700, TRUE);

	std::string pitList = "|| Pit_Entry_Light  || Pit_Exit_Light || Refuel || Visor || Debris || (F) Jacking (B) || (FL FR) Wheel_Nut (BL BR) || (FL FR) Old_Wheel (BL BR) || (FL FR) New_Wheel (BL BR) ||";
	CThread supervisorThread(Supervisor, ACTIVE, NULL);

	Technician jackingFront("jackingFront", 500, pitList.find("Jacking") - 3, 1);
	Technician jackingBack("jackingBack", 500, pitList.find("Jacking") + 9, 1);

	Technician nutFWL("nutRemovedFront", 1000, pitList.find("Wheel_Nut") - 7, 2);
	Technician removeFWL("oldWheelFront", 500, pitList.find("Old_Wheel") - 7, 2);
	Technician replaceFWL("newWheelFront", 1500, pitList.find("New_Wheel") - 7, 2);
	Technician nutFWR("nutRemovedFront", 1000, pitList.find("Wheel_Nut") - 3, 2);
	Technician removeFWR("oldWheelFront", 500, pitList.find("Old_Wheel") - 3, 2);
	Technician replaceFWR("newWheelFront", 1500, pitList.find("New_Wheel") - 3, 2);

	Technician nutBKL("nutRemovedBack", 1000, pitList.find("Wheel_Nut") + 11, 2);
	Technician removeBKL("oldWheelBack", 1500, pitList.find("Old_Wheel") + 11, 2);
	Technician replaceBKL("newWheelBack", 500, pitList.find("New_Wheel") + 11, 2);
	Technician nutBKR("nutRemovedBack", 1000, pitList.find("Wheel_Nut") + 15, 2);
	Technician removeBKR("oldWheelBack", 1500, pitList.find("Old_Wheel") + 15, 2);
	Technician replaceBKR("newWheelBack", 500, pitList.find("New_Wheel") + 15, 2);

	Technician visor("visor", 1000, pitList.find("Visor"),1);
	Technician debris("debris", 2000, pitList.find("Debris"),1);
	Technician refuel("refuel", 3000, pitList.find("Refuel"),1);

	jackingFront.Resume();
	jackingBack.Resume();

	nutFWL.Resume();
	removeFWL.Resume();
	replaceFWL.Resume();
	nutFWR.Resume();
	removeFWR.Resume();
	replaceFWR.Resume();

	nutBKL.Resume();
	removeBKL.Resume();
	replaceBKL.Resume();
	nutBKR.Resume();
	removeBKR.Resume();
	replaceBKR.Resume();

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
	printf("|| Car || Lap || Finished ||");
	monitorMutex.Signal();

	printCar();
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

	MOVE_CURSOR(0, 15);

	cout << endl << "(1): indicates technician is working." << endl;
	cout << "(0): indicates technician is free." << endl;

	MOVE_CURSOR(0, 26);		// some lines are displaced due to the escape sequences, \\ displays as \

	cout << "                                        _.....____......._____.._                                        " << endl;
	cout << "                                  _..--'    || ======\\ \\========== `-._                                   " << endl;
	cout << "                         ______.-''         ||        \\ \\             \\ \\`-. _                             " << endl;
	cout << "                        /_      \\ \\_________||_________\\ \\_____________\\ \\____''_-..__                    " << endl;
	cout << "     _.-. _             00|      _.----._              |               |          _.._`--. _             " << endl;
	cout << "  _.(    ) ),--.        00|    .'+..--..+`.   ~ ~ ~ ~  | ~ ~ ~ ~ ~ ~ ~ | ~ ~ ~ .'.---..`.    '-._        " << endl;
	cout << "(               )-._   \\0|   /++/  __  \\++\\  ~ ~ ~ ~  | (^^^) ~ ~ ~ ~ | ~ ~  /+/  __  \\+\\       0033    " << endl;
	cout << " ( _________________) ___|  |++|  /  \\  |++|          |               |     /+|  /  \\  |+|       \\003   " << endl;
	cout << "                       \___\\_|++|  \\__/  |++|__________|_______________|_____|+|  \\__/  |+|__________3   " << endl;
	cout << "     VROOM VROOM           \\W\\++\\      /++/W_W_W_W_W_W_W_W_W_W_W_W_W_W_W_W_W_\\+\\      /+/_W_W_W_W_W/    " << endl;
	cout << "                               \\+`===='+/                                     `+`===='+'                " << endl;
	cout << "==========================================================================================================" << endl;
	
	monitorMutex.Signal();
}

void printCar() {
	monitorMutex.Wait();
	MOVE_CURSOR(0, 13);

	cout << "								           _________        " << endl;
	cout << "								          / /  || \\ \\       " << endl;
	cout << "								      ___/ /___||__\\ \\____  " << endl;
	cout << "								= =  /  _          _     () " << endl;
	cout << "								= =  \\_/ \\________/ \\____/  " << endl;
	cout << "								_______\\_/________\\_/_________ " << endl;

	cout << endl << "(1): indicates technician is working." << endl;
	cout << "(0): indicates technician is free.";
	monitorMutex.Signal();
}