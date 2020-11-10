#pragma once
#include "../../rt.h"


// Structures
struct elevatorStatus {
	UINT currentFloor;
	bool headingDirection;		// true = up, false = down
	bool outOfOrder;
	bool doorStatus;			
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
CSemaphore ElevatorIOProducer1("ElevatorIOProducer1", 0, 1);
CSemaphore ElevatorIOProducer2("ElevatorIOProducer2", 0, 1);
CSemaphore ElevatorIOConsumer1("ElevatorIOConsumer1", 0, 1);
CSemaphore ElevatorIOConsumer2("ElevatorIOConsumer2", 0, 1);
// Dispatcher
CSemaphore ElevatorDispatcherProducer1("ElevatorDispatcherProducer1", 0, 1);
CSemaphore ElevatorDispatcherProducer2("ElevatorDispatcherProducer2", 0, 1);
CSemaphore ElevatorDispatcherConsumer1("ElevatorDispatcherConsumer1", 0, 1);
CSemaphore ElevatorDispatcherConsumer2("ElevatorDispatcherConsumer2", 0, 1);


CDataPool dpIoDispatcher("dpIoDispatcher", sizeof(struct IOData));

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