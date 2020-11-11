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

struct IOData {
	char input1;
	char input2;
};

// Semaphores
// IO - Dispatcher
CSemaphore IOProducer("IOProducer", 0);
CSemaphore IOConsumer("IOConsumer", 1);

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

// Terminal output mutex
CMutex terminalOutput("TerminalOutput", 1);

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