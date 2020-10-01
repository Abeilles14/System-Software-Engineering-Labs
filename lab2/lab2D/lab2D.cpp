#include "../../rt.h"

UINT __stdcall ChildThread1(void* args);
UINT __stdcall ChildThread2(void* args);

struct threadInfo {
	std::string threadName;
	int iterations;
	std::string threadMessage;
};

int main() {
	threadInfo thread1;
	thread1.threadName = "First thread";
	thread1.iterations = 100;
	thread1.threadMessage = "Hello from thread 1\n";

	threadInfo thread2;
	thread2.threadName = "Second thread";
	thread2.iterations = 200;
	thread2.threadMessage = "Hello from thread 2\n";

	CThread t1(ChildThread1, ACTIVE, &thread1);
	CThread t2(ChildThread2, ACTIVE, &thread2);

	t1.WaitForThread();
	t2.WaitForThread();

	return 0;
}

UINT __stdcall ChildThread1(void* args) {
	threadInfo myThread = *(threadInfo*)(args);		// args points to any data passed to the child thread
													// by the parent thread during the call

	cout << "This thread's name is " << myThread.threadName << " running for " << myThread.iterations << " iterations\n\n";

	for (int i = 0; i < myThread.iterations; i++) {
		cout << myThread.threadMessage;
		Sleep(20);
	}

	return 0;
}

UINT __stdcall ChildThread2(void* args) {
	threadInfo myThread = *(threadInfo*)(args);		// args points to any data passed to the child thread
													// by the parent thread during the call
	cout << "This thread's name is " << myThread.threadName << " running for " << myThread.iterations << " iterations\n\n";

	for (int i = 0; i < myThread.iterations; i++) {
		cout << myThread.threadMessage;
		Sleep(20);
	}

	return 0;
}