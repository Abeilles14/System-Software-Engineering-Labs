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

UINT __stdcall commandThread(void* args) {
	struct IOData* dataPointer;
	dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();
	std::string input;

	for (;;) {
		struct IOData* dataPointer;
		dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();

		IOProducer.Wait();
		cout << "consuming data...\n" << dataPointer->input1 << dataPointer->input2 << endl;
		
		switch (dataPointer->input1) {
		case '1':
			elevator1Dest = (UINT)(dataPointer->input2 - '0');
			cout << "Elevator 1 dest:" << elevator1Dest << endl;
			break;

		case '2':
			elevator2Dest = (UINT)(dataPointer->input2 - '0');
			cout << "Elevator 2 dest:" << elevator2Dest << endl;;
			break;

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



int main() {
	CThread thread1(commandThread, ACTIVE, NULL);






	// INSERT LOGIC TO DETERMINE WHICH ELEVATOR TO SEND A COMMAND TO

	thread1.WaitForThread();

	return 0;
}