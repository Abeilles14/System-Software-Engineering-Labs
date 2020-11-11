#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>
#include "../constants.h"

UINT __stdcall keyboardThread(void* args) {
	struct IOData* dataPointer;
	dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();

	std::string input;
	bool exit_flag = false;

	for (;;) {

		terminalOutput.Wait();
		MOVE_CURSOR(0, 0);
		cout << "Input new data into pipeline\n";		
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		// Waiting for input...
		std::getline(std::cin, input);

		if (input.length() != 2) {
			cout << "Invalid length";
			continue;
		}

		if (input[0] != '1' && input[0] != '2' && input[0] != 'u' && input[0] != 'd' && input[0] != 'e') {
			cout << "Invalid 1st input";
			continue;
		}

		if (!isdigit(input[1]) || (input[0] == 'e' && input[1] != 'e')) {
			cout << "Invalid 2nd input";
			continue;
		}

		if (input[1] == 'e') {		// exit sequence, return elevators to ground, open doors, end sim.
			cout << "Ending simulation, returning elevators to ground floor";
			exit_flag = true;
		}

		// Wait for function to be consumed after valid input as been issued
		IOConsumer.Wait();

		cout << "Writing data to pipeline...";
		dataPointer->input1 = input[0];
		dataPointer->input2 = input[1];

		// Signal new data is available
		IOProducer.Signal();

		if (exit_flag == true) {
			break;
		}
	}

	return 0;
}

UINT __stdcall elevatorStatusIOThread1(void* args) {
	Named ElevatorMonitor1(monitorElevator1, 1);
	elevatorStatus currentStatus;

	terminalOutput.Wait();
	MOVE_CURSOR(0, 5);
	cout << "Elevator 1 on floor " << 0;
	MOVE_CURSOR(0, 1);
	terminalOutput.Signal();

	for(;;) {

		ElevatorIOProducer1.Wait();
		ElevatorMonitor1.get_elevator_status(currentStatus);
		ElevatorIOConsumer1.Signal();



		// Display on terminal output
		terminalOutput.Wait();
		MOVE_CURSOR(0, 5);
		cout << "Elevator 1 on floor " << currentStatus.currentFloor;
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		// produce data for IO C1 (done in elevator in dispatcher)
	}

	return 0;
}

UINT __stdcall elevatorStatusIOThread2(void* args) {
	Named ElevatorMonitor2(monitorElevator2, 2);
	elevatorStatus currentStatus;

	terminalOutput.Wait();
	MOVE_CURSOR(0, 6);
	cout << "Elevator 2 on floor " << 0;
	MOVE_CURSOR(0, 1);
	terminalOutput.Signal();

	for(;;) {
		ElevatorIOProducer2.Wait();
		ElevatorMonitor2.get_elevator_status(currentStatus);
		ElevatorIOConsumer2.Signal();



		// Display on terminal output
		terminalOutput.Wait();
		MOVE_CURSOR(0, 6);
		cout << "Elevator 2 on floor " << currentStatus.currentFloor;
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();
	}

	return 0;
}

int main() {
	CThread keyboardThread(keyboardThread, ACTIVE, NULL);
	CThread elevatorStatusIOThread1(elevatorStatusIOThread1, ACTIVE, NULL);
	CThread elevatorStatusIOThread2(elevatorStatusIOThread2, ACTIVE, NULL);

	keyboardThread.WaitForThread();

	return 0;
}