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