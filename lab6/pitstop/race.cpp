#include "../../rt.h"
#include "Technician.h"
#include "Driver.h"


#define NUMBER_OF_PITSTOPS 10

UINT __stdcall Driver(void* args);


UINT __stdcall Driver(void* args) {
	for (;;) {

	}

	return 0;
}

int main()
{

	CThread driver(Driver, ACTIVE, NULL);

	for (;;) {

	}

	driver.WaitForThread();			// wait for thread to die

	return 0;
}