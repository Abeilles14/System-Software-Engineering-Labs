#include "../../rt.h"
#include "Elevator.h"

using namespace std;

struct elevatorStatus {
	int currentFloor;
	std::string headingDirection;
	std::string doorStatus;
	bool outOfOrder;
};

struct	elevatorStatus* elevatorStatusPtr1;
struct	elevatorStatus* elevatorStatusPtr2;

UINT __stdcall Dispatcher(void* args) {

	//	Create a datapool and then get a pointer to it

	CDataPool dpStatus1(" elevatorStatusPtr1", sizeof(struct elevatorStatus));
	CDataPool dpStatus2(" elevatorStatusPtr2", sizeof(struct elevatorStatus));
	
	elevatorStatusPtr1 = (struct elevatorStatus*)dpStatus1.LinkDataPool();
	elevatorStatusPtr2 = (struct elevatorStatus*)dpStatus2.LinkDataPool();

	// create elevator active classes here?

}

UINT __stdcall IO(void* args) {

}

int main()
{
	CThread dispatcherThread(Dispatcher, ACTIVE, NULL);

	return 0;
}