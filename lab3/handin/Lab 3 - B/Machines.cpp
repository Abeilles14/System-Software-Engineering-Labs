#include "../../rt.h"
#include "CoffeeMaker.h"
#include "WashingMachine.h"
#include <iostream>

int main() {
	CoffeeMaker coffeeMaker1(1);
	CoffeeMaker coffeeMaker2(2);
	CoffeeMaker coffeeMaker3(3);
	CoffeeMaker coffeeMaker4(4);
	CoffeeMaker coffeeMaker5(5);

	WashingMachine washingMachine1(1);
	WashingMachine washingMachine2(2);
	WashingMachine washingMachine3(3);
	WashingMachine washingMachine4(4);
	WashingMachine washingMachine5(5);

	// exit suspended state 
	coffeeMaker1.Resume();
	coffeeMaker2.Resume();
	coffeeMaker3.Resume();
	coffeeMaker4.Resume();
	coffeeMaker5.Resume();

	washingMachine1.Resume();
	washingMachine2.Resume();
	washingMachine3.Resume();
	washingMachine4.Resume();
	washingMachine5.Resume();

	// start and pause machines randomly
	coffeeMaker4.Start();
	washingMachine1.Start();

	Sleep(3000);

	coffeeMaker5.Start();			// CM5 will start to completion, then remain in IDLE
	washingMachine2.Start();		// WM2 will start to completion, then remain in IDLE
	
	Sleep(3000);

	coffeeMaker4.Stop();			// pauses CM4 in current state
	washingMachine1.Stop();			// pauses WM4 in current state

	Sleep(3000);

	// turning all machines off
	coffeeMaker1.End();
	coffeeMaker2.End();
	coffeeMaker3.End();
	coffeeMaker4.End();
	coffeeMaker5.End();

	washingMachine1.End();
	washingMachine2.End();
	washingMachine3.End();
	washingMachine4.End();
	washingMachine5.End();

	coffeeMaker1.WaitForThread();
	coffeeMaker2.WaitForThread();
	coffeeMaker3.WaitForThread();
	coffeeMaker4.WaitForThread();
	coffeeMaker5.WaitForThread();

	washingMachine1.WaitForThread();
	washingMachine2.WaitForThread();
	washingMachine3.WaitForThread();
	washingMachine4.WaitForThread();
	washingMachine5.WaitForThread();

	return 0;
}