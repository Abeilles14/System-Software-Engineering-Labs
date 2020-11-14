#include "../../rt.h"
#include <chrono>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include "../constants.h"

bool exit_flag = false;
int passenger_count = 0;
UINT passengerCurrFloor = 0;
UINT passengerDestFloor = 0;
UINT elevatorNum = 0;

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

		// Waiting for input 1
		input1 = _getch();
		cout << input1;

		if (input1 != '1' && input1 != '2' && input1 != 'u' && input1 != 'd' && input1 != 'e' && input1 != '+' && input1 != '-') {
			cout << "\n\rInvalid 1st input            ";
			continue;
		}

		// Waiting for input 2
		input2 = _getch();
		cout << input2 << "\n";

		if (!isdigit(input2) && input2 != 'e') {
			cout << "\rInvalid 2nd input             ";
			continue;
		}

		if (input1 == 'e' && input2 == 'e') {		// exit sequence, return elevators to ground, open doors, end sim
			exit_flag = true;
		}

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
	// Elevator conditions
	CCondition* Elevator1Floor[10];

	// 0 = down, 1 = up
	CCondition* Elevator1UpOrDown[2];
	CCondition* Elevator1Open;

	CCondition* Elevator1Available;

	// C Condition intializiation
	// Floors
	for (uint8_t index = 0; index < 10; index++) {
		Elevator1Floor[index] = new CCondition("Elevator1Floor" + std::to_string(index));
	}

	// Up or down
	for (uint8_t index = 0; index < 2; index++) {
		Elevator1UpOrDown[index] = new CCondition("Elevator1UpOrDown" + std::to_string(index));
	}

	// Open
	Elevator1Open = new CCondition("Elevator1Open");
	Elevator1Available = new CCondition("Elevator1Available");


	Named* ElevatorMonitor1 = new Named(monitorElevator1, 1);
	elevatorStatus currentStatus1 = { 0, 0, 0, 0, 0 };

	terminalOutput.Wait();
	MOVE_CURSOR(0, 5);
	printf("Elevator 1 on floor 0");
	MOVE_CURSOR(0, 1);
	terminalOutput.Signal();

	for(;;) {
		ElevatorIOProducer1.Wait();
		Elevator1Floor[currentStatus1.currentFloor]->Reset();
		ElevatorMonitor1->get_elevator_status(currentStatus1);
		ElevatorIOConsumer1.Signal();

		// Display on terminal output
		terminalOutput.Wait();
		MOVE_CURSOR(0, 5);
		printf("Elevator 1 on floor %d with %d passengers", currentStatus1.currentFloor, elevator1PassengerNumber);
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		// Update elevator condition flags

		// Signal current floor
		Elevator1Floor[currentStatus1.currentFloor]->Signal();

		// Signal up or down
		if (currentStatus1.headingDirection) {
			Elevator1UpOrDown[1]->Signal();
			Elevator1UpOrDown[0]->Reset();
		}
		else {
			Elevator1UpOrDown[0]->Signal();
			Elevator1UpOrDown[1]->Reset();
		}

		// Signal door status
		if (currentStatus1.doorStatus) {
			Elevator1Open->Signal();
		}
		else {
			Elevator1Open->Reset();
		}

		// Available
		if (currentStatus1.available) {
			Elevator1Available->Signal();
		}
		else {
			Elevator1Available->Reset();
		}

		if (currentStatus1.currentFloor == 0 && exit_flag) {
			break;
		}
	}

	return 0;
}

UINT __stdcall elevatorStatusIOThread2(void* args) {
	// Elevator conditions
	CCondition* Elevator2Floor[10];
	// 0 = down, 1 = up
	CCondition* Elevator2UpOrDown[2];
	CCondition* Elevator2Open;
	CCondition* Elevator2Available;


	// C Condition intializiation
// Floors
	for (uint8_t index = 0; index < 10; index++) {
		Elevator2Floor[index] = new CCondition("Elevator2Floor" + std::to_string(index));
	}

	// Up or down
	for (uint8_t index = 0; index < 2; index++) {
		Elevator2UpOrDown[index] = new CCondition("Elevator2UpOrDown" + std::to_string(index));
	}

	// Open
	Elevator2Open = new CCondition("Elevator2Open");

	// Available
	Elevator2Available = new CCondition("Elevator2Available");

	Named *ElevatorMonitor2 = new Named(monitorElevator2, 2);
	elevatorStatus currentStatus2 = {0, 0, 0, 0, 0};

	terminalOutput.Wait();
	MOVE_CURSOR(0, 6);
	printf("Elevator 2 on floor 0");
	MOVE_CURSOR(0, 1);
	terminalOutput.Signal();

	for(;;) {
		ElevatorIOProducer2.Wait();
		Elevator2Floor[currentStatus2.currentFloor]->Reset();
		ElevatorMonitor2->get_elevator_status(currentStatus2);
		ElevatorIOConsumer2.Signal();

		// Display on terminal output
		terminalOutput.Wait();
		MOVE_CURSOR(0, 6);
		printf("Elevator 2 on floor %d with %d passengers", currentStatus2.currentFloor, elevator2PassengerNumber);
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		// Update elevator condition flags

		// Clear any existing flags

		// Signal current floor
		Elevator2Floor[currentStatus2.currentFloor]->Signal();
		
		// Signal current direction
		if (currentStatus2.headingDirection) {
			Elevator2UpOrDown[1]->Signal();
			Elevator2UpOrDown[0]->Reset();
		}
		else {
			Elevator2UpOrDown[0]->Signal();
			Elevator2UpOrDown[1]->Reset();
		}

		// Signal door status
		if (currentStatus2.doorStatus) {
			Elevator2Open->Signal();
		}
		else {
			Elevator2Open->Reset();
		}

		// Available
		if (currentStatus2.available) {
			Elevator2Available->Signal();
		}
		else {
			Elevator2Available->Reset();
		}

		if (currentStatus2.currentFloor == 0 && exit_flag) {
			
			break;
		}
	}

	return 0;
}

// Generate passengers
UINT __stdcall passengerThread(void* args) {
	Passenger* passengerPtr = NULL;

	while (!exit_flag) {
		srand(time(NULL));
		// Generate number between 0 and 9
		// Anytime between 3 and 8 seconds
		Sleep(rand() % 6000);
		passengerPtr = new Passenger();
		passengerPtr->Resume();
	}
	return 0;
}

int main() {
	CThread keyboardThread(keyboardThread, ACTIVE, NULL);
	CThread elevatorStatusThread1(elevatorStatusIOThread1, ACTIVE, NULL);
	CThread elevatorStatusThread2(elevatorStatusIOThread2, ACTIVE, NULL);
	CThread passengerThread1(passengerThread, ACTIVE, NULL);

	CProcess DispatcherProcess("dispatcher.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	CProcess AsciiProcess("assignment1.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);


	// IO dispatcher datapool
	struct IOData* dataPointer;
	dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();

	// Passenger IO datapool
	struct PassengerData* passengerDataPointer;
	passengerDataPointer = (struct PassengerData*)dpPassengerIO.LinkDataPool();
	Sleep(50);
	Passenger* passengerPtr = NULL;

	passengerPtr = new Passenger();
	passengerPtr->Resume();

	for(;;) {

		PassengerProducer.Wait();		// wait until data consumed before producing more data
		//cout << "IO consuming Passenger data...\n" << passengerDataPointer->input1 << passengerDataPointer->input2 << endl;

		// send data to dispatcher
		IOConsumer.Wait();
		//cout << "\rWriting Passenger data to IO Dispatcher pipeline...";
		dataPointer->input1 = passengerDataPointer->input1;
		dataPointer->input2 = passengerDataPointer->input2;

		// Signal new data is available
		IOProducer.Signal();
		PassengerConsumer.Signal();

	}

	DispatcherProcess.WaitForProcess();
	// DISPATCHER CLOSED
	keyboardThread.WaitForThread();
	// KEYBOARD THREAD CLOSED
	elevatorStatusThread1.WaitForThread(1000);
	elevatorStatusThread2.WaitForThread(1000);
	AsciiProcess.WaitForProcess(1000);

	return 0;
}