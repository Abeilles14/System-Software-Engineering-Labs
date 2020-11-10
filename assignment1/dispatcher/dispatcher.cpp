#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>
#include "../constants.h"

UINT elevator1Floor;
UINT elevator2Floor;

UINT elevator1Dest;
UINT elevator2Dest;

// Which floor was the elevator called from
UINT waitingFloor;

// 0 = down, 1 = up
bool waitingDirection;

// Threads
UINT __stdcall commandThread(void* args);
UINT __stdcall elevatorThread(void* args);

int main() {
	UINT elevatorNumberOne = 1;
	UINT elevatorNumberTwo = 2;

	CThread commandThread(commandThread, ACTIVE, NULL);
	CThread elevatorThread1(elevatorThread, ACTIVE, &elevatorNumberOne);
	CThread elevatorThread2(elevatorThread, ACTIVE, &elevatorNumberTwo);

	CProcess IOProcess("IO.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	// INSERT LOGIC TO DETERMINE WHICH ELEVATOR TO SEND A COMMAND TO
	Named Elevator2Monitor;

	IOProcess.WaitForProcess();

	commandThread.WaitForThread();
	elevatorThread1.WaitForThread();
	elevatorThread2.WaitForThread();

	return 0;
}

// Elevators
UINT __stdcall elevatorThread(void* args) {
	
	CMailbox elevatorMailbox;
	UINT message;

	UINT destinationFloor = 0;
	elevatorStatus currentStatus = { 0, 0, 0, 0 };

	for (;;) {
		
		// If a new command has been receieved and the elevator is available
		if (elevatorMailbox.TestForMessage()) {
			message = elevatorMailbox.GetMessage();

			destinationFloor = message;
		}

		// If elevator is out of order
		if (currentStatus.outOfOrder) {
			continue;
		}

		// Move to floor needed
		while (destinationFloor != currentStatus.currentFloor) {
			if (currentStatus.outOfOrder) {
				break;
			}

			// Time between elevator movements
			Sleep(2000);
			if (currentStatus.currentFloor < destinationFloor) {
				currentStatus.headingDirection = 1;
				currentStatus.currentFloor++;
			}

			else {
				currentStatus.headingDirection = 0;
				currentStatus.currentFloor--;
			}
		}

	

	}

}

UINT __stdcall commandThread(void* args) {
	//Named terminalControl = *(Named*)(args);
	struct IOData* dataPointer;
	dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();
	std::string input;

	for (;;) {
		struct IOData* dataPointer;
		dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();

		IOProducer.Wait();
		cout << "consuming data...\n" << dataPointer->input1 << dataPointer->input2 << endl;

		switch (dataPointer->input1) {
		// Inside the elevator
		case '1':
			elevator1Dest = (UINT)(dataPointer->input2 - '0');
			cout << "Elevator 1 dest:" << elevator1Dest << endl;
			break;

		case '2':
			elevator2Dest = (UINT)(dataPointer->input2 - '0');
			cout << "Elevator 2 dest:" << elevator2Dest << endl;;
			break;

		// Outside the elevator
		case 'u':
			waitingFloor = (UINT)(dataPointer->input2 - '0');
			waitingDirection = 1;
			cout << "Elevator requested on floor " << waitingFloor << " to go up" << endl;;
			break;

		case 'd':
			waitingFloor = (UINT)(dataPointer->input2 - '0');
			waitingDirection = 0;
			cout << "Elevator requested on floor " << waitingFloor << " to go down" << endl;;
			break;

		default:
			cout << "CRITICAL ERROR";
			break;

		}

		IOConsumer.Signal();
	}

	return 0;
}