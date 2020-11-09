#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>
#include "constants.h"

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

UINT __stdcall elevatorThread1(void* args) {
	// Code to Get_Elevator_Status from 1 and display on monitor here
	return 0;
}

UINT __stdcall elevatorThread2(void* args) {
	// Code to Get_Elevator_Status from 2 and display on monitor here
	return 0;
}

int main() {
	CThread thread1(keyboardThread, ACTIVE, NULL);
	CThread thread2(elevatorThread1, ACTIVE, NULL);
	CThread thread3(elevatorThread2, ACTIVE, NULL);

	thread1.WaitForThread();

	return 0;
}