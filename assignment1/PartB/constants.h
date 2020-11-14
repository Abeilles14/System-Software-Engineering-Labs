#pragma once
#include "../../rt.h"
#include <vector>

enum elevatorCommand {
	noCommand,
	firstElevator,
	secondElevator,
	requestUp,
	requestDown
};

// Structures
struct elevatorStatus {
	UINT currentFloor;
	bool headingDirection;		// 1 = up, 0 = down
	bool outOfOrder;			// 1 = out of order, 0 = in order
	bool doorStatus;			// 0 = closed, 1 = open
	bool available;				// 0 = busy, 1 = free
};

struct passengerStatus {
	UINT currentFloor;
	UINT destinationFloor;
	UINT elevatorNumber;
	bool inElevator;
	bool arrivedDestination;
};

struct IOData {
	char input1;
	char input2;
};

struct PassengerData {
	char currentFloor;
	char upOrDown;
	char destinationFloor;
	char elevatorNumber;
	char input1;
	char input2;
};

static const UINT elevatorTime = 500;

// Mutex Terminal Output
CMutex terminalOutput("TerminalOutput", 1);

// Semaphores
// IO - Dispatcher
CSemaphore IOProducer("IOProducer", 0);
CSemaphore IOConsumer("IOConsumer", 1);

// Passenger - IO
CSemaphore PassengerProducer("PassengerProducer", 0);
CSemaphore PassengerConsumer("PassengerConsumer", 1);

// Monitor
CSemaphore MonitorOutput("MonitorOutput", 1);

CMutex ElevatorRequest("ElevatorRequest");

// Elevator Status
// IO
CSemaphore ElevatorIOProducer1("ElevatorIOProducer1", 0, 1);
CSemaphore ElevatorIOProducer2("ElevatorIOProducer2", 0, 1);
CSemaphore ElevatorIOConsumer1("ElevatorIOConsumer1", 1, 1);
CSemaphore ElevatorIOConsumer2("ElevatorIOConsumer2", 1, 1);
// Dispatcher
CSemaphore ElevatorDispatcherProducer1("ElevatorDispatcherProducer1", 0, 1);
CSemaphore ElevatorDispatcherProducer2("ElevatorDispatcherProducer2", 0, 1);
CSemaphore ElevatorDispatcherConsumer1("ElevatorDispatcherConsumer1", 1, 1);
CSemaphore ElevatorDispatcherConsumer2("ElevatorDispatcherConsumer2", 1, 1);

// Elevator Passengers
CSemaphore Elevator1Passengers("Elevator1Passengers", 4, 4);
CSemaphore Elevator2Passengers("Elevator2Passengers", 4, 4);

uint8_t elevator1PassengerNumber = 0;
uint8_t elevator2PassengerNumber = 0;

uint16_t totalPassengers = 0;

// Datapools
CDataPool dpIoDispatcher("dpIoDispatcher", sizeof(struct IOData));
CDataPool dpPassengerIO("dpPassengerIO", sizeof(struct PassengerData));

// monitor names
std::string monitorElevator1 = "elevator1";
std::string monitorElevator2 = "elevator2";
std::string monitorPassenger = "passenger";

// Objects
class Named {
private:
	CMutex* sharedMutex;
	elevatorStatus* dataPointer;

	// Datapools
	CDataPool* dpStatus;

public:
	Named(std::string mutexName, UINT elevatorNumber) {
		this->sharedMutex = new CMutex("__MonitorMutex__" + mutexName);
		this->dpStatus = new CDataPool("elevatorStatusPtr" + elevatorNumber, sizeof(elevatorStatus));
		this->dataPointer = (struct elevatorStatus*)dpStatus->LinkDataPool();
	}

	~Named() {
		delete this->sharedMutex;
		delete this->dataPointer;
		delete this->dpStatus;
	}

	void get_elevator_status(elevatorStatus &updatedStatus) {
		this->sharedMutex->Wait();

		updatedStatus = *dataPointer;

		this->sharedMutex->Signal();
	}

	void update_elevator_status(elevatorStatus updatedStatus) {
		this->sharedMutex->Wait();

		*dataPointer = updatedStatus;

		this->sharedMutex->Signal();
	}
};

// Objects
class NamedPassenger {
private:
	CMutex* sharedMutex;
	passengerStatus* passengerDataPointer;

	// Datapools
	CDataPool* dpPassengerStatus;

public:
	NamedPassenger(std::string mutexName) {
		this->sharedMutex = new CMutex("__MonitorMutex__" + mutexName);
		this->dpPassengerStatus = new CDataPool("passengerStatusPtr", sizeof(elevatorStatus));
		this->passengerDataPointer = (struct passengerStatus*)dpPassengerStatus->LinkDataPool();
	}

	~NamedPassenger() {
		delete this->sharedMutex;
		delete this->passengerDataPointer;
		delete this->dpPassengerStatus;
	}

	void get_passenger_status(passengerStatus &updatedStatus) {
		this->sharedMutex->Wait();

		updatedStatus = *passengerDataPointer;

		this->sharedMutex->Signal();
	}

	void update_passenger_status(passengerStatus updatedStatus) {
		this->sharedMutex->Wait();

		*passengerDataPointer = updatedStatus;

		this->sharedMutex->Signal();
	}
};

class Passenger : public ActiveClass {
private:
	UINT currentFloor;
	UINT destinationFloor;
	UINT elevatorNumber;		// on which elevator	0 = off, 1 = EV1, 2 = EV2
	bool upOrDown;

	// Elevator conditions
	CCondition* Elevator1Floor[10];

	// 0 = down, 1 = up
	CCondition* Elevator1UpOrDown[2];
	CCondition* Elevator1Open;
	CCondition* Elevator1Available;

	CCondition* Elevator2Floor[10];
	// 0 = down, 1 = up
	CCondition* Elevator2UpOrDown[2];
	CCondition* Elevator2Open;
	CCondition* Elevator2Available;

public:
	Passenger() {
		// C Condition intializiation
		// Floors
		for (uint8_t index = 0; index < 10; index++) {
			Elevator1Floor[index] = new CCondition("Elevator1Floor" + std::to_string(index));
			Elevator2Floor[index] = new CCondition("Elevator2Floor" + std::to_string(index));
		}

		// Up or down
		for (uint8_t index = 0; index < 2; index++) {
			Elevator1UpOrDown[index] = new CCondition("Elevator1UpOrDown" + std::to_string(index));
			Elevator2UpOrDown[index] = new CCondition("Elevator2UpOrDown" + std::to_string(index));
		}

		// Open
		Elevator1Open = new CCondition("Elevator1Open");
		Elevator2Open = new CCondition("Elevator2Open");

		// Available
		Elevator1Available = new CCondition("Elevator1Available");
		Elevator2Available = new CCondition("Elevator2Available");


		srand(time(NULL));
		// Generate number between 0 and 9
		currentFloor = rand() % 9;
		destinationFloor = rand() % 9;

		// going up
		if (currentFloor < destinationFloor) {
			upOrDown = 1;
		}
		// going down
		else {
			upOrDown = 0;
		}
		elevatorNumber = 0;

		totalPassengers++;
		terminalOutput.Wait();
		MOVE_CURSOR(0, 7);
		printf("TOTAL PASSENGERS: %d", totalPassengers);
		MOVE_CURSOR(0, 1);
		terminalOutput.Signal();
	}

	~Passenger() {
	}

	int main() {
		struct PassengerData* passengerDataPointer;
		passengerDataPointer = (struct PassengerData*)dpPassengerIO.LinkDataPool();

		while (1) {				// currently only lets 1 passenger call at a time...
			//create passengers

			terminalOutput.Wait();
			MOVE_CURSOR(0, 20);
			printf("Passenger is waiting on floor %d and wants to go to floor %d\n", currentFloor, destinationFloor);
			MOVE_CURSOR(0, 1);
			terminalOutput.Signal();

			// Wait for function to be consumed after valid input as been issued
			// Issue new data to the IO
			PassengerConsumer.Wait();

			if (upOrDown) {
				passengerDataPointer->input1 = 'u';	
			}
			else {
				passengerDataPointer->input1 = 'd';
			}
			
			passengerDataPointer->input2 = char('0' + currentFloor);		// send curr floor and direction in dp as char

			// Signal new data is available
			PassengerProducer.Signal();

			// Wait until either elevator is available
			for (;;) {
				if (Elevator1Floor[currentFloor]->Wait(10) == WAIT_TIMEOUT || 
					(Elevator1UpOrDown[upOrDown]->Wait(10) == WAIT_TIMEOUT && Elevator1Available->Wait(10) == WAIT_TIMEOUT) ||
					Elevator1Open->Wait(10) == WAIT_TIMEOUT) {}
				else {
					if (Elevator1Passengers.Wait(10) == WAIT_TIMEOUT) {
						// If the elevator is full, re-issue the request for next time it comes
						PassengerConsumer.Wait();

						if (upOrDown) {
							passengerDataPointer->input1 = 'u';
						}
						else {
							passengerDataPointer->input1 = 'd';
						}

						passengerDataPointer->input2 = char('0' + currentFloor);		// send curr floor and direction in dp as char

						// Signal new data is available
						PassengerProducer.Signal();
						Sleep(500);
					}

					else {
						elevatorNumber = 1;
						elevator1PassengerNumber++;
						break;
					}

				}


				if (Elevator2Floor[currentFloor]->Wait(10) == WAIT_TIMEOUT ||
					(Elevator2UpOrDown[upOrDown]->Wait(10) == WAIT_TIMEOUT && Elevator2Available->Wait(10) == WAIT_TIMEOUT) ||
					Elevator2Open->Wait(10) == WAIT_TIMEOUT) {
				}
				else {
					// If unavailable, re-issue request
					if (Elevator2Passengers.Wait(10) == WAIT_TIMEOUT) {
						PassengerConsumer.Wait();

						if (upOrDown) {
							passengerDataPointer->input1 = 'u';
						}
						else {
							passengerDataPointer->input1 = 'd';
						}

						passengerDataPointer->input2 = char('0' + currentFloor);		// send curr floor and direction in dp as char

						// Signal new data is available
						PassengerProducer.Signal();
						Sleep(10000);
					}

					else {
						elevatorNumber = 2;
						elevator2PassengerNumber++;
						break;
					}
				}
			}

			terminalOutput.Wait();
			MOVE_CURSOR(0, 21);
			printf("\rPassenger Boarding Elevator %d", elevatorNumber);
			MOVE_CURSOR(0, 1);
			terminalOutput.Signal();

			PassengerConsumer.Wait();
			//MOVE_CURSOR(0, 10);
			//printf("\rWriting destination floor to Passenger IO pipeline...");
			//MOVE_CURSOR(0, 1);
			passengerDataPointer->input1 = char('0' + elevatorNumber);
			passengerDataPointer->input2 = char('0' + destinationFloor);		// send curr floor and direction in dp as char
			PassengerProducer.Signal();

			// Wait to arrive at correct floor
			for (;;) {
				if (elevatorNumber == 1) {
					if (Elevator1Floor[destinationFloor]->Wait(10) == WAIT_TIMEOUT || Elevator1Open->Wait(10) == WAIT_TIMEOUT) {}
					else {
						elevator1PassengerNumber--;
						Elevator1Passengers.Signal();
						break;
					}
				}
				
				else {
					if (Elevator2Floor[destinationFloor]->Wait(10) == WAIT_TIMEOUT || Elevator2Open->Wait(10) == WAIT_TIMEOUT) {}
					else {
						elevator2PassengerNumber--;
						Elevator2Passengers.Signal();
						break;
					}

				}
			}
			//ExitElevator.Wait();		// timeout condition: wait for IO to send elevator to floor and open doors

			totalPassengers--;
			terminalOutput.Wait();
			MOVE_CURSOR(0, 22);
			printf("Passenger is exiting on floor %d\n", destinationFloor);
			MOVE_CURSOR(0, 7);
			printf("\rTOTAL PASSENGERS: %d ", totalPassengers);
			MOVE_CURSOR(0, 1);
			terminalOutput.Signal();

			// Destroy Passenger
			return 0;
		}
	}
};