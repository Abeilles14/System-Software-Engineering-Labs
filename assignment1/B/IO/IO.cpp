#include "../../rt.h"
#include <chrono>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include "../constants.h"

bool exit_flag = false;

// Terminal output mutex
CMutex terminalOutput("TerminalOutput", 1);


UINT __stdcall keyboardThread(void* args) {
	struct IOData* dataPointer;
	dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();

	//std::string input;
	char input1 = NULL;
	char input2 = NULL;

	while (!exit_flag) {

		terminalOutput.Wait();
		MOVE_CURSOR(0, 0);
		printf("Input new data into pipeline");	
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		

		// Wait for function to be consumed after valid input as been issued
		IOConsumer.Wait();
		cout << "\rWriting data to pipeline...";
		dataPointer->input1 = input1;
		dataPointer->input2 = input2;

		// Signal new data is available
		IOProducer.Signal();
	}

	return 0;
}

UINT __stdcall elevatorStatusIOThread1(void* args) {
	Named* ElevatorMonitor1 = new Named(monitorElevator1, 1);
	elevatorStatus currentStatus;

	terminalOutput.Wait();
	MOVE_CURSOR(0, 5);
	printf("Elevator 1 on floor 0");
	MOVE_CURSOR(0, 1);
	terminalOutput.Signal();

	for(;;) {

		ElevatorIOProducer1.Wait();
		ElevatorMonitor1->get_elevator_status(currentStatus);
		ElevatorIOConsumer1.Signal();

		// Display on terminal output
		terminalOutput.Wait();
		MOVE_CURSOR(0, 5);
		printf("Elevator 1 on floor %d", currentStatus.currentFloor);
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		if (currentStatus.currentFloor == 0 && exit_flag) {
			break;
		}
	}

	return 0;
}

UINT __stdcall elevatorStatusIOThread2(void* args) {
	Named *ElevatorMonitor2 = new Named(monitorElevator2, 2);
	elevatorStatus currentStatus;

	terminalOutput.Wait();
	MOVE_CURSOR(0, 6);
	printf("Elevator 2 on floor 0");
	MOVE_CURSOR(0, 1);
	terminalOutput.Signal();

	for(;;) {
		ElevatorIOProducer2.Wait();
		ElevatorMonitor2->get_elevator_status(currentStatus);
		ElevatorIOConsumer2.Signal();



		// Display on terminal output
		terminalOutput.Wait();
		MOVE_CURSOR(0, 6);
		printf("Elevator 2 on floor %d", currentStatus.currentFloor);
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		if (currentStatus.currentFloor == 0 && exit_flag) {
			
			break;
		}
	}

	return 0;
}

int main() {
	CThread keyboardThread(keyboardThread, ACTIVE, NULL);
	CThread elevatorStatusThread1(elevatorStatusIOThread1, ACTIVE, NULL);
	CThread elevatorStatusThread2(elevatorStatusIOThread2, ACTIVE, NULL);

	CProcess DispatcherProcess("dispatcher.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	for (;;) {

	}

	DispatcherProcess.WaitForProcess();
	keyboardThread.WaitForThread();
	elevatorStatusThread1.WaitForThread();
	elevatorStatusThread2.WaitForThread();

	return 0;
}