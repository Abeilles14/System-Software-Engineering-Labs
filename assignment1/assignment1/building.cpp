#include "../../rt.h"
#include "Elevator.h"
#include "../constants.h"

using namespace std;

// Elevators
UINT __stdcall elevatorThread(void* args) {
	UINT whichElevator = *(UINT*)(args);

	CSemaphore IOProducer("ElevatorIOProducer" + whichElevator, 0);
	CSemaphore IOConsumer("ElevatorIOConsumer" + whichElevator, 0);
	CSemaphore DispatcherProducer("ElevatorDispatcherProducer" + whichElevator, 0);
	CSemaphore ElevatorDispatcherConsumerIOProducor("ElevatorDispatcherConsumer" + whichElevator, 0);

	struct	elevatorStatus* elevatorStatusPtr;

	CDataPool dpStatus("elevatorStatusPtr" + whichElevator, sizeof(struct elevatorStatus));

	elevatorStatusPtr = (struct elevatorStatus*)dpStatus.LinkDataPool();

	for (;;) {

	}

}

int main()
{

	CProcess p1("IO.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	CProcess p2("Dispatcher.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		PARENT_WINDOW,
		ACTIVE
	);

	p2.WaitForProcess();



	return 0;
}