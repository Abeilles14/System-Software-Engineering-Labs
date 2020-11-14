#include "../../rt.h"
#include <chrono>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include "../constants.h"

void drawBuilding();
void drawElevator1(int cursorX, int cursorY);
void drawElevator2(int cursorX, int cursorY);
void eraseElevator(int cursorX, int cursorY);

bool exit_flag = false;

UINT __stdcall elevatorStatusAsciiThread1(void* args) {
	Named* ElevatorMonitor1 = new Named(monitorElevator1, 1);
	elevatorStatus currentStatus;

	for (;;) {

		ElevatorIOProducer1.Wait();
		ElevatorMonitor1->get_elevator_status(currentStatus);
		ElevatorIOConsumer1.Signal();

		// Display on terminal output
		terminalOutput.Wait();

		MOVE_CURSOR(50, 44 - 4 * (currentStatus.currentFloor));
		printf("EV1 %d", currentStatus.doorStatus);
		MOVE_CURSOR(50, 44 - 4 * (currentStatus.currentFloor) + 4);
		printf("     ");
		MOVE_CURSOR(50, 44 - 4 * (currentStatus.currentFloor) - 4);
		printf("     ");

		terminalOutput.Signal();

		if (currentStatus.currentFloor == 0 && exit_flag) {
			break;
		}
	}

	return 0;
}

UINT __stdcall elevatorStatusAsciiThread2(void* args) {
	Named* ElevatorMonitor2 = new Named(monitorElevator2, 2);
	elevatorStatus currentStatus;

	for (;;) {
		ElevatorIOProducer2.Wait();
		ElevatorMonitor2->get_elevator_status(currentStatus);
		ElevatorIOConsumer2.Signal();

		// Display on terminal output
		terminalOutput.Wait();

		MOVE_CURSOR(34, 44 - 4 * (currentStatus.currentFloor));
		printf("EV2 %d", currentStatus.doorStatus);
		MOVE_CURSOR(34, 44 - 4 * (currentStatus.currentFloor) + 4);
		printf("     ");
		MOVE_CURSOR(34, 44 - 4 * (currentStatus.currentFloor) - 4);
		printf("     ");

		terminalOutput.Signal();

		if (currentStatus.currentFloor == 0 && exit_flag) {

			break;
		}
	}

	return 0;
}

int main() {
	//system("mode 650");

	HWND console = GetConsoleWindow();
	RECT rect;
	GetWindowRect(console, &rect);
	MoveWindow(console, rect.left, rect.top, 2000, 1400, TRUE);

	drawBuilding();

	CThread elevatorStatusThread1(elevatorStatusAsciiThread1, ACTIVE, NULL);
	CThread elevatorStatusThread2(elevatorStatusAsciiThread2, ACTIVE, NULL);

	elevatorStatusThread1.WaitForThread();
	elevatorStatusThread2.WaitForThread();
	return 0;
}

void drawBuilding() {
	MOVE_CURSOR(0, 0);

	cout << R"(                                                  _II__|
					         [[__] |           
			   /^^^^^^,^.^^^^^^^^^^^^^\|__|^^^\
			  /     ,',-.`.               \    \
			 /    ,','   `.`.          ,-"""-.  \
			/___,','__   __`.`._______/_,"T"._\__\
			|WWWW|_|_|_9_|_|_|WWW|_|_|_9_|_|_|WWWW|
			|= ==|           | = |           |= ==|
			|= ==|           |== |           |= ==|
			|^^^^|___________|^^^|___________|^^^^|
			|WWWW|_|_|_8_|_|_|WWW|_|_|_8_|_|_|WWWW|
			|= ==|           | = |           |= ==|
			|= ==|           |== |           |= ==|
			|^^^^|___________|^^^|___________|^^^^|
			|WWWW|_|_|_7_|_|_|WWW|_|_|_7_|_|_|WWWW|
			|= ==|           | = |           |= ==|
			|== =|           | = |           |== =|
			|^^^^|___________|^^^|___________|^^^^|
			|WWWW|_|_|_6_|_|_|WWW|_|_|_6_|_|_|WWWW|
			|= ==|           | = |           |= ==|
			|== =|           | = |           |== =|
			|^^^^|___________|^^^|___________|^^^^|
			|WWWW|_|_|_5_|_|_|WWW|_|_|_5_|_|_|WWWW|
			|= ==|           | = |           |= ==|
			|= ==|           |== |           |= ==|
			|^^^^|___________|^^^|___________|^^^^|
			|WWWW|_|_|_4_|_|_|WWW|_|_|_4_|_|_|WWWW|
			|= ==|           | = |           |= ==|
			|== =|           | = |           |== =|
			|= ==|___________|== |___________|= ==|
			|WWWW|_|_|_3_|_|_|WWW|_|_|_3_|_|_|WWWW|
			|= ==|           | = |           |= ==|
			|== =|           | = |           |== =|
			|= ==|___________|== |___________|= ==|
			|WWWW|_|_|_2_|_|_|WWW|_|_|_2_|_|_|WWWW|
			|= ==|           | = |           |= ==|
			|== =|           |= =|           |== =|
			|= ==|___________|== |___________|= ==|
			|WWWW|_|_|_1_|_|_|WWW|_|_|_1_|_|_|WWWW|
			|== =|           |= =|           |== =|
			|= ==|           |== |           |= ==|
			|^^^^|___________|^^^|___________|^^^^|
			|WWWW|_|_|_0_|_|_|WWW|_|_|_0_|_|_|WWWW|
			|= ==|           | = |           |= ==|
			|== =|           | = |           |== =|
			|= ==|___________|== |___________|= ==|
			|====|MMMMMMMMMMM|===|MMMMMMMMMMM|====|)";

}

void drawPassengers(int cursorX, int cursorY) {
	MOVE_CURSOR(cursorX, cursorY);
	//cout << number;
	cout << R"(  0
                /|\
                / \)";
}

void drawElevator1(int cursorX, int cursorY) {
	MOVE_CURSOR(cursorX, cursorY);
	cout << R"(
                              |  _____  |
                              |o|     |o|
                              |o|     |o|
                              | |_____| |)";
}

void drawElevator2(int cursorX, int cursorY) {
	MOVE_CURSOR(cursorX, cursorY);
	cout << R"(
                                              |  _____  |
                                              |o|     |o|
                                              |o|     |o|
                                              | |_____| |)";
}

void eraseElevator(int cursorX, int cursorY) {
	MOVE_CURSOR(cursorX, cursorY);
	cout << R"(
                          
                          
                          
                          )";
}

/*
|  _____  |
|o|  0 1|o|
|o| /|\ |o|
| |_/_\_| |


			|= ==|           |== |           |= ==|
			|^^^^|___________|^^^|___________|^^^^|
			|WWWW|_|_|_0_|_|_|WWW|_|_|_0_|_|_|WWWW|
			|= ==||  _____  || = |           |= ==|
			|= ==||o|  0 3|o||== |           |= ==|
			|== =||o| /|\ |o|| = |           |== =|
			|= ==||_|_/_\_|_||== |___________|= ==|
			|====|MMMMMMMMMMM|===|MMMMMMMMMMM|====|)"
*/