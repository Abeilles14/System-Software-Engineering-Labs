#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>
#include "../constants.h"

// monitor names
std::string monitorElevator1 = "elevator1";
std::string monitorElevator2 = "elevator2";

UINT __stdcall keyboardThread(void* args) {
	struct IOData* dataPointer;
	dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();
	std::string input;

	for (;;) {

		cout << "Input new data into pipeline\n";
		// Waiting for input...
		std::getline(std::cin, input);

		if (input.length() != 2) {
			cout << "Invalid length";
			continue;
		}

		if (input[0] != '1' && input[0] != '2' && input[0] != 'u' && input[0] != 'd') {
			cout << "Invalid input 1st";
			continue;
		}

		if (!isdigit(input[1])) {
			cout << "Invalid input 2nd";
			continue;
		}

		// Wait for function to be consumed after valid input as been issued
		IOConsumer.Wait();

		cout << "Writing data to pipeline...";
		dataPointer->input1 = input[0];
		dataPointer->input2 = input[1];

		// Signal new data is available
		IOProducer.Signal();
	}

	return 0;
}

UINT __stdcall elevatorStatusIOThread1(void* args) {
	Named ElevatorMonitor1(monitorElevator1, 1);

	for(;;) {
		ElevatorIOConsumer1.Wait();
		ElevatorDispatcherConsumer1.Wait();

		// produce data for IO C1 (done in elevator in dispatcher)

		ElevatorIOProducer1.Signal();

		// produce data for Dispatcher C1 (done in elevator in dispatcher)

		ElevatorIOProducer2.Signal();
	}

	return 0;
}

UINT __stdcall elevatorStatusIOThread2(void* args) {
	Named ElevatorMonitor2(monitorElevator2, 2);

	for(;;) {
		ElevatorIOConsumer2.Wait();
		ElevatorDispatcherConsumer2.Wait();

		// produce data for IO C2 (done in elevator in dispatcher)

		ElevatorIOProducer1.Signal();

		// produce data for Dispatcher C2 (done in elevator in dispatcher)

		ElevatorIOProducer2.Signal();
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