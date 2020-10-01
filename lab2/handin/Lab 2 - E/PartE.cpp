#include <iostream>
#include <windows.h>	// for perror and sleep
#include <process.h>

#define UINT unsigned int

UINT __stdcall ChildThread1(void* args);
UINT __stdcall ChildThread2(void* args);

struct threadInfo {
	std::string threadName;
	int iterations;
	std::string threadMessage;
};

int main()
{
	threadInfo thread1;
	UINT thread1ID = 0;
	thread1.threadName = "First thread";
	thread1.iterations = 100;
	thread1.threadMessage = "Hello from thread 1\n";

	threadInfo thread2;
	UINT thread2ID = 0;
	thread2.threadName = "Second thread";
	thread2.iterations = 200;
	thread2.threadMessage = "Hello from thread 2\n";

	// Thread setup
	UINT flags = NORMAL_PRIORITY_CLASS; // Priority,

	HANDLE ThreadHandle1 = (HANDLE)(_beginthreadex(NULL, 0, ChildThread1, &thread1, flags, &thread1ID));
	if (ThreadHandle1 == 0) {
		std::cout << "Unable to Create Thread";
		return 0;
	}

	Sleep(100);

	HANDLE ThreadHandle2 = (HANDLE)(_beginthreadex(NULL, 0, ChildThread2, &thread2, flags, &thread2ID));
	if (ThreadHandle2 == 0) {
		std::cout << "Unable to Create Thread";
		return 0;
	}
	Sleep(100);

	std::cout << "Waiting for thread 1 to finish\n";
	if (WaitForSingleObject(ThreadHandle1, INFINITE) == WAIT_FAILED) {
		std::cout << "Unable to Wait for Thread 1" ;
		return 0;
	}

	std::cout << "Waiting for thread 2 to finish\n";
	if (WaitForSingleObject(ThreadHandle2, INFINITE) == WAIT_FAILED) {
		std::cout << "Unable to Wait for Thread 2";
		return 0;
	}

	return 0;
}

UINT __stdcall ChildThread1(void* args) {
	 threadInfo myThread = *(threadInfo*)(args);

	 std::cout << "This thread's name is " << myThread.threadName << " running for " << myThread.iterations << " iterations\n\n";

	for (int i = 0; i < myThread.iterations; i++) {
		std::cout << myThread.threadMessage;
		Sleep(20);
	}

	return 0;
}

UINT __stdcall ChildThread2(void* args) {
	threadInfo myThread = *(threadInfo*)(args);

	std::cout << "This thread's name is " << myThread.threadName << " running for " << myThread.iterations << " iterations\n\n";

	for (int i = 0; i < myThread.iterations; i++) {
		std::cout << myThread.threadMessage;
		Sleep(20);
	}

	return 0;
}