#include "../../rt.h"
#include <atomic>

UINT __stdcall Child1(void* args);
UINT __stdcall Child2(void* args);
UINT __stdcall Child3(void* args);

atomic_flag flag;

int main(void) {
	CThread t1(Child1, ACTIVE, NULL);		// create the 3 other child threads
	CThread t2(Child2, ACTIVE, NULL);
	CThread t3(Child3, ACTIVE, NULL);

	for (int i = 0; i < 50000; i++) {
		while (flag.test_and_set() == true);	// TAS

		MOVE_CURSOR(5, 5);             	// move cursor to cords [x,y] = 5,5
		printf("Parent");
		fflush(stdout);		      	// force output to be written to screen now

		flag.clear();
	}

	t1.WaitForThread();			// wait for the 3 other child threads to end
	t2.WaitForThread();
	t3.WaitForThread();

	cout << "Child Threads have ended\n";

	return 0;
}

UINT __stdcall Child1(void* args) {
	for (int i = 0; i < 50000; i++) {
		while (flag.test_and_set() == true);	// TAS

		MOVE_CURSOR(10, 20);             	// move cursor to cords [x,y] = 5,5
		printf("Thread 1");
		fflush(stdout);		      	// force output to be written to screen now

		flag.clear();
	}

	return 0;
}

UINT __stdcall Child2(void* args) {
	for (int i = 0; i < 50000; i++) {
		while (flag.test_and_set() == true);	// TAS

		MOVE_CURSOR(10, 30);             	// move cursor to cords [x,y] = 5,5
		printf("Thread 2");
		fflush(stdout);		      	// force output to be written to screen now

		flag.clear();
	}

	return 0;
}

UINT __stdcall Child3(void* args) {
	for (int i = 0; i < 50000; i++) {
		while (flag.test_and_set() == true);	// TAS

		MOVE_CURSOR(10, 540);             	// move cursor to cords [x,y] = 5,5
		printf("Thread 3");
		fflush(stdout);		      	// force output to be written to screen now

		flag.clear();
	}

	return 0;
}