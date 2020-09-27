#include <windows.h>
#include <iostream>

using namespace std;

int main() {
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION pInfo;
	UINT flags = NORMAL_PRIORITY_CLASS; // Priority
	BOOL Success;
	UINT Result;

	const string& pathChild1 = "C:\\Users\\Isabelle\\Documents\\UBC_ELEC\\CPEN333\\Labs\\lab2\\lab2\\Debug\\lab2Child1.exe";

	StartupInfo = {
		sizeof(STARTUPINFO) ,
		NULL ,			// reserved
		NULL ,			// ignored in console applications
		(char*)(pathChild1.c_str()) ,	// displayed in title bar for console applications
		0,0,			// dwx, dwy, offset of top left of new window relative to top left of screen in pixel
						// flags below must specify STARTF_USEPOSITION. Ignored for console apps'
		0,0,			// dwxsize, dwysize: Width and height of the window if new window specified
						// must use flags STARTF_USESIZE. Ignored for console apps'
		0,0,			// size of console in characters, only if STARTF_USECOUNTCHARS flag specified, 
						// Ignored for console apps
		0,				// Colour control, for background and text. Ignored for console apps
		0,				// Flags. Ignored for console applications
		0,				// ignored unless showwindow flag set
		0 ,
		NULL,
		0,0,0			// stdin, stdout and stderr handles (inherited from parent)
	};

	cout << "Creating a Child1 Process\n";

	Success = CreateProcess(
		NULL,	// application name
		(char*)(pathChild1.c_str()),	// Command line to the process if you want to pass one to main() in the process
		NULL,			// process attributes
		NULL,			// thread attributes
		TRUE,			// inherits handles of parent
		flags,			// Priority and Window control flags,
		NULL,			// use environent of parent
		NULL,			// use same drive and directory as parent
		&StartupInfo,	// controls appearance of process (see above)
		&pInfo			// Stored process handle and ID into this object
	);
	if (!Success) {
		cout << "Error creating Child1 process\n";
		return -1;
	}

	Sleep(1000);

	cout << "\nChild1 is suspended\n";
	Result = SuspendThread(pInfo.hThread);
	if (Result == 0xffffffff) {
		cout << "Error suspening Child1 process\n";
		return -1;
	}

	Sleep(2000);

	cout << "\nChild1 is resuming\n";
	Result = ResumeThread(pInfo.hThread);
	if (Result == 0xffffffff) {
		cout << "Error resuming Child1 process\n";
		return -1;
	}

	// Wait until child process exits.
	WaitForSingleObject(pInfo.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pInfo.hProcess);
	CloseHandle(pInfo.hThread);

	cout << "\nChild1 process has ended\n";

	return 0;
}