#pragma once
#include "../../rt.h"


// Structures
struct elevatorStatus {
	int currentFloor;
	bool headingDirection;
	bool outOfOrder;
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
CSemaphore ElevatorIOProducer1("ElevatorIOProducer1", 0);
CSemaphore ElevatorIOProducer2("ElevatorIOProducer2", 0);
CSemaphore ElevatorIOConsumer1("ElevatorIOConsumer1", 0);
CSemaphore ElevatorIOConsumer2("ElevatorIOConsumer2", 0);
// Dispatcher
CSemaphore ElevatorDispatcherProducer1("ElevatorDispatcherProducer1", 0);
CSemaphore ElevatorDispatcherProducer2("ElevatorDispatcherProducer2", 0);
CSemaphore ElevatorDispatcherConsumer1("ElevatorDispatcherConsumer1", 0);
CSemaphore ElevatorDispatcherConsumer2("ElevatorDispatcherConsumer2", 0);


// Datapools
CDataPool dpStatus1("elevatorStatusPtr1", sizeof(struct elevatorStatus));
CDataPool dpStatus2("elevatorStatusPtr2", sizeof(struct elevatorStatus));

CDataPool dpIoDispatcher("dpIoDispatcher", sizeof(struct IOData));