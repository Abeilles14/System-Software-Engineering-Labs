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
	UINT elevatorNumber;
};

static const UINT elevatorTime = 500;

// Synchronization CCondition 
CCondition EnterElevator("Enter");   		// create a non-signalled condition
CCondition ExitElevator("Exit");

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
CSemaphore ElevatorIOProducer1("ElevatorIOProducer1", 0, 1);		//TODO: fix initial 0,1 values
CSemaphore ElevatorIOProducer2("ElevatorIOProducer2", 0, 1);
CSemaphore ElevatorIOConsumer1("ElevatorIOConsumer1", 1, 1);
CSemaphore ElevatorIOConsumer2("ElevatorIOConsumer2", 1, 1);
// Dispatcher
CSemaphore ElevatorDispatcherProducer1("ElevatorDispatcherProducer1", 0, 1);
CSemaphore ElevatorDispatcherProducer2("ElevatorDispatcherProducer2", 0, 1);
CSemaphore ElevatorDispatcherConsumer1("ElevatorDispatcherConsumer1", 1, 1);
CSemaphore ElevatorDispatcherConsumer2("ElevatorDispatcherConsumer2", 1, 1);

// Datapools
CDataPool dpIoDispatcher("dpIoDispatcher", sizeof(struct IOData));
CDataPool dpPassengerIO("dpPassengerIO", sizeof(struct PassengerData));

// monitor names
std::string monitorElevator1 = "elevator1";
std::string monitorElevator2 = "elevator2";

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

	void update_elevator_status(passengerStatus updatedStatus) {
		this->sharedMutex->Wait();

		*passengerDataPointer = updatedStatus;

		this->sharedMutex->Signal();
	}
};

class Passenger : public ActiveClass {
public:
	UINT currentFloor;
	UINT destinationFloor;
	UINT elevatorNumber;		// on which elevator	0 = off, 1 = EV1, 2 = EV2
	UINT passengerNumber = 0;		// passenger count/number
	char upOrDown;

	Passenger(int number) {
		this->passengerNumber = number;

		srand(time(NULL));
		// Generate number between 0 and 9
		currentFloor = rand() % 9;
		destinationFloor = rand() % 9;

		// going up
		if (currentFloor < destinationFloor) {
			upOrDown = 'u';
		}
		// going down
		else {
			upOrDown = 'd';
		}

		elevatorNumber = 0;
	}

	~Passenger() {
	}

	int main() {

		return 0;
	}

};