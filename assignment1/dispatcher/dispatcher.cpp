#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include "../constants.h"

elevatorStatus elevator1;
elevatorStatus elevator2;

UINT elevator1Dest = 0;
UINT elevator2Dest = 0;

// Which floor was the elevator called from
UINT waitingFloor = 0;

// 0 = down, 1 = up
bool waitingDirection;
bool elevatorOutOfOrder[2] = { 0 };

UINT currentCommand;

bool exit_flag = false;

// Threads
UINT __stdcall commandThread(void* args);
UINT __stdcall elevatorThread(void* args);
UINT __stdcall elevatorStatusThread1(void* args);
UINT __stdcall elevatorStatusThread2(void* args);

using namespace std;

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

	while (!exit_flag) {
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
			// Check if either elevator is free
			if (elevator1.available == true && abs((int)(elevator1Dest - waitingFloor)) <= abs((int)(elevator2Dest - waitingFloor))) {
				elevatorThread1.Post(waitingFloor);
				elevator1Dest = waitingFloor;
			}

			else if (elevator2.available == true && abs((int)(elevator1Dest - waitingFloor)) >= abs((int)(elevator2Dest - waitingFloor))) {
				elevatorThread2.Post(waitingFloor);
				elevator2Dest = waitingFloor;
			}
			
			else if (elevator1.headingDirection == 1) {
				elevatorThread1.Post(waitingFloor);
				elevator1Dest = waitingFloor;
			}
			else if (elevator2.headingDirection == 1) {
				elevatorThread2.Post(waitingFloor);
				elevator2Dest = waitingFloor;
			}

			// If neither elevator is near/on its way, check which one is nearest and send it based on last destination
			else if (abs((int)(elevator1Dest - waitingFloor)) < abs((int)(elevator2Dest - waitingFloor))) {
				elevatorThread1.Post(waitingFloor);
				elevator1Dest = waitingFloor;
			}
			else {
				elevatorThread2.Post(waitingFloor);
				elevator2Dest = waitingFloor;
			}
			currentCommand = noCommand;
			break;

		case requestDown:
			// Check if either elevator is free
			if (elevator1.available == true && abs((int)(elevator1Dest - waitingFloor)) <= abs((int)(elevator2Dest - waitingFloor))) {
				elevatorThread1.Post(waitingFloor);
				elevator1Dest = waitingFloor;
			}

			else if (elevator2.available == true && abs((int)(elevator1Dest - waitingFloor)) >= abs((int)(elevator2Dest - waitingFloor))) {
				elevatorThread2.Post(waitingFloor);
				elevator2Dest = waitingFloor;
			}

			else if (elevator1.headingDirection == 0) {
				elevatorThread1.Post(waitingFloor);
				elevator1Dest = waitingFloor;
			}
			else if (elevator2.headingDirection == 0) {
				elevatorThread2.Post(waitingFloor);
				elevator2Dest = waitingFloor;
			}

			// If neither elevator is near/on its way, check which one is nearest and send it based on last destination
			else if (abs((int)(elevator1Dest - waitingFloor)) < abs((int)(elevator2Dest - waitingFloor))) {
				elevatorThread1.Post(waitingFloor);
				elevator1Dest = waitingFloor;
			}
			else {
				elevatorThread2.Post(waitingFloor);
				elevator2Dest = waitingFloor;
			}
			currentCommand = noCommand;
			break;

		case noCommand:
		default:
			break;

		}
	}

	IOProcess.WaitForProcess();
	printf("IO CLOSED\n");
	commandThread.WaitForThread();
	printf("COMAND THREAD CLOSED\n");
	elevatorThread1.WaitForThread();
	printf("ELEVATOR 1 CLOSED\n");
	elevatorThread2.WaitForThread();
	printf("ELEVATOR 2 CLOSED\n");

	return 0;
}

// Elevators
UINT __stdcall elevatorThread(void* args) {
	UINT elevatorNumber = *(UINT*)(args);

	// monitor class
	Named * ElevatorMonitor = new Named("elevator" + elevatorNumber, elevatorNumber);

	CSemaphore ElevatorIOProducer("ElevatorIOProducer" + std::to_string(elevatorNumber), 0, 1);
	CSemaphore ElevatorIOConsumer("ElevatorIOConsumer" + std::to_string(elevatorNumber), 1, 1);
	CSemaphore ElevatorDispatcherProducer("ElevatorDispatcherProducer" + std::to_string(elevatorNumber), 0, 1);
	CSemaphore ElevatorDispatcherConsumer("ElevatorDispatcherConsumer" + std::to_string(elevatorNumber), 1, 1);

	CMailbox elevatorMailbox;
	UINT message;

	UINT destinationFloor = 0;
	elevatorStatus currentStatus = { 0, 1, 0, 0, 1};	// default: floor 0, going up, in order, doors closed, available

	// Update initial status
	ElevatorIOConsumer.Wait();
	ElevatorDispatcherConsumer.Wait();

	ElevatorMonitor->update_elevator_status(currentStatus);

	ElevatorDispatcherProducer.Signal();
	ElevatorIOProducer.Signal();

	for (;;) {
		// If a new command has been receieved and the elevator is available
		if (elevatorMailbox.TestForMessage() && !exit_flag) {
			message = elevatorMailbox.GetMessage();

			destinationFloor = message;
		}

		if (exit_flag) {
			destinationFloor = 0;

			if (currentStatus.currentFloor == 0) {
				ElevatorIOConsumer.Wait();
				ElevatorDispatcherConsumer.Wait();

				ElevatorMonitor->update_elevator_status(currentStatus);

				ElevatorDispatcherProducer.Signal();
				ElevatorIOProducer.Signal();
				return 0;
			}
		}

		// If elevator is out of order
		if (elevatorOutOfOrder[elevatorNumber-1]) {
			printf("elevator %d out of order\n", elevatorNumber);

			while (elevatorOutOfOrder[elevatorNumber - 1]) {
				ElevatorIOConsumer.Wait();
				ElevatorDispatcherConsumer.Wait();

				currentStatus.outOfOrder = 1;
				currentStatus.available = 0;


				ElevatorDispatcherProducer.Signal();
				ElevatorIOProducer.Signal();

				Sleep(elevatorTime);

			}
			//continue;
		}

		// Close doors
		// Receieved new order, close doors
		if (currentStatus.currentFloor != destinationFloor) {
			ElevatorIOConsumer.Wait();
			ElevatorDispatcherConsumer.Wait();

			currentStatus.doorStatus = 0;
			printf("elevator %d doors closed\n", elevatorNumber);
			
			ElevatorMonitor->update_elevator_status(currentStatus);

			ElevatorDispatcherProducer.Signal();
			ElevatorIOProducer.Signal();
		}

		// Close doors and move to floor needed
		while (currentStatus.currentFloor != destinationFloor) {
			currentStatus.doorStatus = 0;
			currentStatus.available = 0;

			if (elevatorOutOfOrder[elevatorNumber - 1]) {
				break;
			}

			// Time between elevator movements
			Sleep(elevatorTime);
			if (currentStatus.currentFloor < destinationFloor) {
				currentStatus.headingDirection = 1;
				currentStatus.currentFloor++;

				printf("elevator %d going up\n", elevatorNumber);
				printf("elevator %d at floor %d\n", elevatorNumber, currentStatus.currentFloor);
			}

			else {
				currentStatus.headingDirection = 0;
				currentStatus.currentFloor--;
				printf("elevator %d going down\n", elevatorNumber);
				printf("elevator %d at floor %d\n", elevatorNumber, currentStatus.currentFloor);
			}

			ElevatorIOConsumer.Wait();
			ElevatorDispatcherConsumer.Wait();

			ElevatorMonitor->update_elevator_status(currentStatus);

			ElevatorDispatcherProducer.Signal();
			ElevatorIOProducer.Signal();

			if (currentStatus.currentFloor == destinationFloor) {

				ElevatorIOConsumer.Wait();
				ElevatorDispatcherConsumer.Wait();

				currentStatus.doorStatus = 1;
				currentStatus.available = 1;
				printf("elevator %d doors open\n", elevatorNumber);

				ElevatorMonitor->update_elevator_status(currentStatus);

				ElevatorDispatcherProducer.Signal();
				ElevatorIOProducer.Signal();

				// Leave doors open 
				Sleep(elevatorTime);
			}
		}
	}
	return 0;
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

	while (!exit_flag) {
		struct IOData* dataPointer;
		dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();

		IOProducer.Wait();
		cout << "consuming data...\n" << dataPointer->input1 << dataPointer->input2 << endl;

		switch (dataPointer->input1) {
		// Inside the elevator
		case '1':
			elevator1Dest = (UINT)(dataPointer->input2 - '0');
			currentCommand = firstElevator;
			break;

		case '2':
			elevator2Dest = (UINT)(dataPointer->input2 - '0');
			currentCommand = secondElevator;
			break;

		// Outside the elevator
		case 'u':
			waitingFloor = (UINT)(dataPointer->input2 - '0');
			waitingDirection = 1;
			currentCommand = requestUp;
			break;

		case 'd':
			waitingFloor = (UINT)(dataPointer->input2 - '0');
			waitingDirection = 0;
			currentCommand = requestDown;
			break;

		case '+':
			
			if (dataPointer->input2 == '1') {
				elevatorOutOfOrder[0] = false;
			}

			else {
				elevatorOutOfOrder[1] = false;
			}
			break;

		case '-':
			if (dataPointer->input2 == '1') {
				elevatorOutOfOrder[0] = true;
			}

			else {
				elevatorOutOfOrder[1] = true;
			}
			break;

		case 'e':
			waitingFloor = 0;
			waitingDirection = 0;
			currentCommand = requestDown;

			printf("Ending simulation, returning elevators to ground floor\n");
			exit_flag = true;
			break;

		default:
			printf("CRITICAL ERROR, ELEVATOR CRASHING");
			break;
		}

		// Wait for function to be consumed after valid input as been issued
		IOConsumer.Signal();
	}

	return 0;
}