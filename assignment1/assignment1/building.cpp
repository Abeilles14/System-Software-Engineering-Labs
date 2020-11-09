#include "../../rt.h"
#include "Elevator.h"

using namespace std;

struct elevatorStatus {
	int currentFloor;
	std::string headingDirection;
	std::string doorStatus;
	bool inOrder;
};

struct	elevatorStatus* elevatorStatusPtr1;
struct	elevatorStatus* elevatorstatusPtr2;

UINT __stdcall Dispatcher(void* args) {

}

UINT __stdcall IO(void* args) {

}

int main()
{

	return 0;
}