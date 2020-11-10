#include "../../rt.h"
#include "../constants.h"

using namespace std;

int main()
{

	CProcess p1("IO.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE
	);

	CProcess p2("Dispatcher.exe",	// pathlist to child program executable
		NORMAL_PRIORITY_CLASS,
		PARENT_WINDOW,
		ACTIVE
	);

	p2.WaitForProcess();



	return 0;
}