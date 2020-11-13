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

// Terminal output mutex
CMutex terminalOutput("TerminalOutput", 1);

elevatorStatus currentStatus2;
elevatorStatus currentStatus1;

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

	terminalOutput.Wait();
	MOVE_CURSOR(0, 5);
	printf("Elevator 1 on floor 0");
	MOVE_CURSOR(0, 1);
	terminalOutput.Signal();

	for(;;) {

		ElevatorIOProducer1.Wait();
		ElevatorMonitor1->get_elevator_status(currentStatus1);
		ElevatorIOConsumer1.Signal();

		// Display on terminal output
		terminalOutput.Wait();
		MOVE_CURSOR(0, 5);
		printf("Elevator 1 on floor %d", currentStatus1.currentFloor);
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		if (currentStatus1.currentFloor == 0 && exit_flag) {
			break;
		}
	}

	return 0;
}

UINT __stdcall elevatorStatusIOThread2(void* args) {
	Named *ElevatorMonitor2 = new Named(monitorElevator2, 2);

	terminalOutput.Wait();
	MOVE_CURSOR(0, 6);
	printf("Elevator 2 on floor 0");
	MOVE_CURSOR(0, 1);
	terminalOutput.Signal();

	for(;;) {
		ElevatorIOProducer2.Wait();
		ElevatorMonitor2->get_elevator_status(currentStatus2);
		ElevatorIOConsumer2.Signal();

		// Display on terminal output
		terminalOutput.Wait();
		MOVE_CURSOR(0, 6);
		printf("Elevator 2 on floor %d", currentStatus2.currentFloor);
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		if (currentStatus2.currentFloor == 0 && exit_flag) {
			
			break;
		}
	}

	return 0;
}

UINT __stdcall passengerThread(void* args) {
	struct PassengerData* passengerDataPointer;
	passengerDataPointer = (struct PassengerData*)dpPassengerIO.LinkDataPool();

	while (!exit_flag) {				// currently only lets 1 passenger call at a time...
		//create passengers
		passenger_count++;
		Passenger passenger(passenger_count);
		NamedPassenger* PassengerMonitor = new NamedPassenger("Passenger" + passenger.passengerNumber);
		
		terminalOutput.Wait();
		MOVE_CURSOR(0, 9);
		printf("Passenger %d is waiting on floor %d\n", passenger.passengerNumber, passenger.currentFloor);
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		// Wait for function to be consumed after valid input as been issued
		PassengerConsumer.Wait();
		MOVE_CURSOR(0, 10);
		printf("\rWriting floor and direction to Passenger IO pipeline...");
		MOVE_CURSOR(0, 1);
		passengerDataPointer->upOrDown = passenger.upOrDown;				// TODO: Use monitor instead to update??
		passengerDataPointer->currentFloor = '0' + passenger.currentFloor;		// send curr floor and direction in dp as char

		// Signal new data is available
		PassengerProducer.Signal();

		EnterElevator.Wait();		// timeout condition, wait for IO to send elevator down and open doors to passenger

		PassengerConsumer.Wait();
		MOVE_CURSOR(0, 10);
		printf("\rWriting destination floor to Passenger IO pipeline...");
		MOVE_CURSOR(0, 1);
		passengerDataPointer->destinationFloor = '0' + passenger.destinationFloor;		// send dest floor in dp
		PassengerProducer.Signal();

		ExitElevator.Wait();		// timeout condition: wait for IO to send elevator to floor and open doors

		passenger.elevatorNumber = 0;		// get off elevator
		terminalOutput.Wait();
		MOVE_CURSOR(0, 9);
		printf("Passenger %d is exiting on floor %d\n", passenger.passengerNumber, passenger.destinationFloor);
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();

		Sleep(2 + (rand() % 6));	// create new passenger every 2-6 sec
	}

	return 0;
}

int main() {
	CThread passengerThread(passengerThread, ACTIVE, NULL);
	//CThread keyboardThread(keyboardThread, ACTIVE, NULL);
	CThread elevatorStatusThread1(elevatorStatusIOThread1, ACTIVE, NULL);
	CThread elevatorStatusThread2(elevatorStatusIOThread2, ACTIVE, NULL);

	CProcess DispatcherProcess("dispatcher.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	// IO dispatcher datapool
	struct IOData* dataPointer;
	dataPointer = (struct IOData*)dpIoDispatcher.LinkDataPool();

	// Passener IO datapool
	struct PassengerData* passengerDataPointer;
	passengerDataPointer = (struct PassengerData*)dpPassengerIO.LinkDataPool();

	for (;;) {
		PassengerProducer.Wait();		// wait until data consumed before producing more data
		cout << "IO consuming data...\n" << passengerDataPointer->upOrDown << passengerDataPointer->currentFloor << endl;		// get waiting passenger data

		// send data to dispatcher
		IOConsumer.Wait();
		cout << "\rWriting data IO Dispatcher pipeline...";
		dataPointer->input1 = passengerDataPointer->upOrDown;
		dataPointer->input2 = passengerDataPointer->currentFloor;

		// Signal new data is available
		IOProducer.Signal();

		PassengerConsumer.Signal();

		// wait until EV1 or EV2 is at passenger pickup floor with open doors and available and in order
		passengerCurrFloor = (UINT)(passengerDataPointer->currentFloor - '0');

		for (;;) {
			if (currentStatus1.currentFloor == passengerCurrFloor && currentStatus1.doorStatus && currentStatus1.available && !currentStatus1.outOfOrder) {
				passengerDataPointer->elevatorNumber = '1';
				break;
			}
			else if (currentStatus2.currentFloor == passengerCurrFloor && currentStatus2.doorStatus && currentStatus2.available && !currentStatus2.outOfOrder) {
				passengerDataPointer->elevatorNumber = '2';
				break;
			}
		}

		// if either elevators arrive at passenger floor, CCondition signal to enter
		EnterElevator.Signal();
		cout << "Passenger boarding elevator " << passengerDataPointer->elevatorNumber << "\n";

		//get new passenger floor destination info
		PassengerProducer.Wait();		// wait until data consumed before producing more data
		
		cout << "consuming data...\n" << passengerDataPointer->elevatorNumber << passengerDataPointer->destinationFloor << endl;		// get waiting passenger data

		// send data to dispatcher
		IOConsumer.Wait();
		cout << "\rWriting destination floor to pipeline...";
		dataPointer->input1 = passengerDataPointer->elevatorNumber;
		dataPointer->input2 = passengerDataPointer->destinationFloor;

		// Signal new data is available
		IOProducer.Signal();

		PassengerConsumer.Signal();

		// wait until passenger's is at passenger dest floor with open doors
		passengerDestFloor = (UINT)(passengerDataPointer->destinationFloor - '0');

		for (;;) {
			if (passengerDataPointer->elevatorNumber == '1') {
				if (currentStatus1.currentFloor == passengerDestFloor && currentStatus1.doorStatus) {
					break;
				}
			}
			else {
				if (currentStatus2.currentFloor == passengerDestFloor && currentStatus2.doorStatus) {
					break;
				}
			}
		}

		//set CCondition to true
		ExitElevator.Signal();

		Sleep(2000);
	}

	passengerThread.WaitForThread();
	DispatcherProcess.WaitForProcess();
	//keyboardThread.WaitForThread();
	elevatorStatusThread1.WaitForThread();
	elevatorStatusThread2.WaitForThread();

	return 0;
}