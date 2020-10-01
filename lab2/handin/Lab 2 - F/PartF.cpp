#include <iostream>
#include <windows.h>	// for perror and sleep
#include <process.h>
#include <thread>

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
	threadInfo threadInfo1;
	UINT thread1ID = 0;
	threadInfo1.threadName = "First thread";
	threadInfo1.iterations = 100;
	threadInfo1.threadMessage = "Hello from thread 1\n";

	threadInfo threadInfo2;
	UINT thread2ID = 0;
	threadInfo2.threadName = "Second thread";
	threadInfo2.iterations = 200;
	threadInfo2.threadMessage = "Hello from thread 2\n";

	std::thread thread1(ChildThread1, &threadInfo1);
	std::thread thread2(ChildThread2, &threadInfo2);

	std::cout << "Waiting for thread 1 to finish...\n";
	thread1.join();
	std::cout << "Waiting for thread 2 to finish...\n";
	thread2.join();

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