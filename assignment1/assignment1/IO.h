#pragma once

#include "../../rt.h"
#include <chrono>
#include <ctime>
#include "constants.h"

UINT __stdcall keyboardThread(void* args) {
	struct IOData* dataPointer;
	dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();
	std::string input;

	for(;;) {

		cout << "Input new data into pipeline\n";
		// Waiting for input...
		std::getline(std::cin, input);

		if (input.length() != 2) {
			cout << "Invalid length";
			continue;
		}

		if (input[0] != '1' && input[0] != '2' && input[0] != 'u') {
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




class IO : public ActiveClass
{
public:

	int main(void) {
		CThread thread1(keyboardThread, ACTIVE, NULL);

		thread1.WaitForThread();

		return 0;
	}
};