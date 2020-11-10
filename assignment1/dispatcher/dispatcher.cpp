#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>
#include "../constants.h"

elevatorStatus elevator1;
elevatorStatus elevator2;

UINT elevator1Dest;
UINT elevator2Dest;

// Which floor was the elevator called from
UINT waitingFloor;

// 0 = down, 1 = up
bool waitingDirection;

UINT currentCommand;

// Threads
UINT __stdcall commandThread(void* args);
UINT __stdcall elevatorThread(void* args);
UINT __stdcall elevatorStatusThread1(void* args);
UINT __stdcall elevatorStatusThread2(void* args);

int main() {
	UINT elevatorNumberOne = 1;
	UINT elevatorNumberTwo = 2;

	CThread commandThread(commandThread, ACTIVE, NULL);
	CThread elevatorThread1(elevatorThread, ACTIVE, &elevatorNumberOne);
	CThread elevatorThread2(elevatorThread, ACTIVE, &elevatorNumberTwo);

	CThread elevatorDispatcherThread1(elevatorStatusThread1, ACTIVE, NULL);
	CThread elevatorDispatcherThread2(elevatorStatusThread2, ACTIVE, NULL);

	CProcess IOProcess("IO.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	// INSERT LOGIC TO DETERMINE WHICH ELEVATOR TO SEND A COMMAND TO

	// named monitors
	Named ElevatorMonitor1(monitorElevator1, 1);
	Named ElevatorMonitor2(monitorElevator2, 2);

	for (;;) {
		switch (currentCommand) {
		case firstElevator:
			elevatorThread1.Post(elevator1Dest);
			currentCommand = noCommand;
			break;

		case secondElevator:
			elevatorThread2.Post(elevator2Dest);
			currentCommand = noCommand;
			break;

		case requestUp:
			// INSERT LOGIC FOR AN UP REQUEST. Probably compares current/destination floor of elevator with source of request
			break;

		case requestDown:
			// INSERT LOGIC FOR AN DOWN REQUEST. Probably compares current/destination floor of elevator with source of request
			break;

		case noCommand:
		default:
			break;

		}
	}

	IOProcess.WaitForProcess();

	commandThread.WaitForThread();
	elevatorThread1.WaitForThread();
	elevatorThread2.WaitForThread();

	return 0;
}

// Elevators
UINT __stdcall elevatorThread(void* args) {
	UINT elevatorNumber = *(UINT*)(args);

	// monitor class
	Named ElevatorMonitor("elevator" + elevatorNumber, elevatorNumber);

	CSemaphore ElevatorIOProducer("ElevatorIOProducer" + std::to_string(elevatorNumber), 0, 1);
	CSemaphore ElevatorIOConsumer("ElevatorIOConsumer" + std::to_string(elevatorNumber), 1, 1);
	CSemaphore ElevatorDispatcherProducer("ElevatorDispatcherProducer" + std::to_string(elevatorNumber), 0, 1);
	CSemaphore ElevatorDispatcherConsumer("ElevatorDispatcherConsumer" + std::to_string(elevatorNumber), 1, 1);

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
		while (currentStatus.currentFloor != destinationFloor) {

			if (currentStatus.outOfOrder) {
				break;
			}

			// Time between elevator movements
			Sleep(500);
			if (currentStatus.currentFloor < destinationFloor) {
				currentStatus.headingDirection = 1;
				currentStatus.currentFloor++;
				cout << "elevator " << elevatorNumber << " rising\n";
			}

			else {
				currentStatus.headingDirection = 0;
				currentStatus.currentFloor--;
				cout << "elevator " << elevatorNumber << " falling\n";
			}

			ElevatorIOConsumer.Wait();
			ElevatorDispatcherConsumer.Wait();
			ElevatorMonitor.update_elevator_status(currentStatus);
			ElevatorDispatcherProducer.Signal();
			ElevatorIOProducer.Signal();
		}
	}
}

UINT __stdcall elevatorStatusThread1(void* args) {
	Named ElevatorMonitor1("elevator1", 1);
	elevatorStatus currentStatus;

	for (;;) {
		ElevatorDispatcherProducer1.Wait();

		ElevatorMonitor1.get_elevator_status(currentStatus);

		ElevatorDispatcherConsumer1.Signal();

		elevator1 = currentStatus;
	}

	return 0;
}

UINT __stdcall elevatorStatusThread2(void* args) {
	Named ElevatorMonitor2(monitorElevator2, 2);
	elevatorStatus currentStatus;

	for (;;) {
		ElevatorDispatcherProducer2.Wait();

		ElevatorMonitor2.get_elevator_status(currentStatus);

		ElevatorDispatcherConsumer2.Signal();

		elevator2 = currentStatus;
	}

	return 0;
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
			//cout << "Elevator 1 dest:" << elevator1Dest << endl;
			currentCommand = firstElevator;
			break;

		case '2':
			elevator2Dest = (UINT)(dataPointer->input2 - '0');
			//cout << "Elevator 2 dest:" << elevator2Dest << endl;;
			currentCommand = secondElevator;
			break;

		// Outside the elevator
		case 'u':
			waitingFloor = (UINT)(dataPointer->input2 - '0');
			waitingDirection = 1;
			//cout << "Elevator requested on floor " << waitingFloor << " to go up" << endl;;
			currentCommand = requestUp;
			break;

		case 'd':
			waitingFloor = (UINT)(dataPointer->input2 - '0');
			waitingDirection = 0;
			//cout << "Elevator requested on floor " << waitingFloor << " to go down" << endl;;
			currentCommand = requestDown;
			break;

		default:
			cout << "CRITICAL ERROR";
			break;

		}

		IOConsumer.Signal();
	}

	return 0;
}