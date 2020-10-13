#include "../../rt.h"
#include <atomic>

UINT __stdcall Child1(void* args);
UINT __stdcall Child2(void* args);
UINT __stdcall Child3(void* args);

std::string monitorClassName = "terminalOutputs";

class Named {
private:
	CMutex* sharedMutex;

public:
	Named(std::string theName) {
		this->sharedMutex = new CMutex("__MonitorMutex__" + theName);
	}

	~Named() {
		delete this->sharedMutex;
		cout << "Mutex deletede";
	}

	void WriteToTerminal(UINT x, UINT y, const char* output) {
		this->sharedMutex->Wait();

		MOVE_CURSOR(x, y);             	// move cursor to cords [x,y]
		cout << output;
		fflush(stdout);		      	// force output to be written to screen now

		this->sharedMutex->Signal();
	}

};

int main(void) {
	Named terminalOutputs(monitorClassName);


	CThread t1(Child1, ACTIVE, &terminalOutputs);		// create the 3 other child threads
	CThread t2(Child2, ACTIVE, &terminalOutputs);
	CThread t3(Child3, ACTIVE, &terminalOutputs);

	for (int i = 0; i < 50000; i++) {
		terminalOutputs.WriteToTerminal(5, 5, "Parent");
	}

	t1.WaitForThread();			// wait for the 3 other child threads to end
	t2.WaitForThread();
	t3.WaitForThread();

	cout << "Child Threads have ended\n";

	return 0;
}

UINT __stdcall Child1(void* args) {
	Named terminalControl = *(Named*)(args);

	for (int i = 0; i < 50000; i++) {
		terminalControl.WriteToTerminal(10, 20, "Thread 1");
	}

	return 0;
}

UINT __stdcall Child2(void* args) {
	Named terminalControl = *(Named*)(args);

	for (int i = 0; i < 50000; i++) {
		terminalControl.WriteToTerminal(10, 30, "Thread 2");
	}

	return 0;
}

UINT __stdcall Child3(void* args) {
	Named terminalControl = *(Named*)(args);

	for (int i = 0; i < 50000; i++) {
		terminalControl.WriteToTerminal(10, 40, "Thread 3");
	}

	return 0;
}
