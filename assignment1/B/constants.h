#pragma once
#include "../../rt.h"

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
CSemaphore Elevator1Passengers("Elevator1Passengers", 1, 4);
CSemaphore Elevator2Passengers("Elevator2Passengers", 1, 4);

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

	CCondition* Elevator2Floor[10];
	// 0 = down, 1 = up
	CCondition* Elevator2UpOrDown[2];
	CCondition* Elevator2Open;

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
	}

	~Passenger() {
	}

	int main() {
		struct PassengerData* passengerDataPointer;
		passengerDataPointer = (struct PassengerData*)dpPassengerIO.LinkDataPool();

		while (1) {				// currently only lets 1 passenger call at a time...
			//create passengers

			terminalOutput.Wait();
			MOVE_CURSOR(0, 9);
			printf("Passenger is waiting on floor %d\n", currentFloor);
			MOVE_CURSOR(0, 1);
			terminalOutput.Signal();

			// Wait for function to be consumed after valid input as been issued
			// Issue new data to the IO
			PassengerConsumer.Wait();
			MOVE_CURSOR(0, 10);
			printf("\rWriting floor and direction to Passenger IO pipeline...");
			MOVE_CURSOR(0, 1);

			if (upOrDown) {
				passengerDataPointer->input1 = 'u';	
			}
			else {
				passengerDataPointer->input1 = 'd';
			}
			
			passengerDataPointer->input2 = '0' + currentFloor;		// send curr floor and direction in dp as char

			// Signal new data is available
			PassengerProducer.Signal();

			// Wait until either elevator is available
			for (;;) {
				if (Elevator1Floor[currentFloor]->Wait(10) == WAIT_TIMEOUT || Elevator1UpOrDown[upOrDown]->Wait(10) == WAIT_TIMEOUT) {}
				else {
					elevatorNumber = 1;
					break;
				}


				if (Elevator2Floor[currentFloor]->Wait(10) == WAIT_TIMEOUT || Elevator2UpOrDown[upOrDown]->Wait(10) == WAIT_TIMEOUT) {}
				else {
					elevatorNumber = 2;
					break;
				}
			}

			printf("\rPassenger Boarding Elevator %d", elevatorNumber);

			PassengerConsumer.Wait();
			MOVE_CURSOR(0, 10);
			printf("\rWriting destination floor to Passenger IO pipeline...");
			MOVE_CURSOR(0, 1);
			passengerDataPointer->input1 = elevatorNumber;				// TODO: Use monitor instead to update??
			passengerDataPointer->input2 = '0' + destinationFloor;		// send curr floor and direction in dp as char
			PassengerProducer.Signal();

			// Wait to arrive at correct floor
			for (;;) {
				if (elevatorNumber == 1) {
					if (Elevator1Floor[currentFloor]->Wait(10) == WAIT_TIMEOUT || Elevator1UpOrDown[upOrDown]->Wait(10) == WAIT_TIMEOUT) {}
					else {
						break;
					}
				}
				
				else {
					if (Elevator2Floor[currentFloor]->Wait(10) == WAIT_TIMEOUT || Elevator2UpOrDown[upOrDown]->Wait(10) == WAIT_TIMEOUT) {}
					else {
						break;
					}

				}
			}
			//ExitElevator.Wait();		// timeout condition: wait for IO to send elevator to floor and open doors

			terminalOutput.Wait();
			MOVE_CURSOR(0, 12);
			printf("Passenger is exiting on floor %d\n", destinationFloor);
			MOVE_CURSOR(0, 1);
			terminalOutput.Signal();

			// Destroy Passenger
			return 0;
		}
	}
};