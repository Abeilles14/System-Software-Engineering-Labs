#include "..\..\rt.h"

struct donutShop {
	const char* name[14];
	int amount;
};

int main() {
	struct donutShop donut;

	cout << "Child2 Process Creating the Pipeline\n";

	CPipe p2("Pipe2");

	cout << "Parent Process Creating Child Process to Read from Pipeline\n";

	donut.name[14] = "Sour Cream";
	p2.Write(&donut.name, sizeof(donut.name));
	cout << "Child2 Writing " << donut.name << " to pipeline\n";

	Sleep(3000);

	donut.amount = 12;
	p2.Write(&donut.amount, sizeof(donut.amount));
	cout << "Child2 Writing " << donut.amount << " to pipeline\n";

	Sleep(10000);

	return 0;
}