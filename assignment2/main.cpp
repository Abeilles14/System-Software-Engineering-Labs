#include "../rt.h"
#include <conio.h>
#include "constants.h"
#include "database.h"

using namespace std;

void processUserInput(int input) {
	switch(input){
		case 0:
			// exit
			break;
		case 1:
			cout << "Accessing course database\n";
			
			break;
		case 2:
			cout << "Accessing student database\n";

			break;
		case 3:
			
			break;
		case 4:
			
			break;
		default:
			cout << "Unrecognized command, please refer to available command list";
	}
}

void setUserInput() {

}

void setUserType() {

}

bool checkUserPrivileges() {

}


int main() {
	int input;
	bool exit_flag;

	while(!exit_flag){
		input = _getch();



		if(input == 0) {
			exit_flag = true;
		}
	}

	return 0;
}