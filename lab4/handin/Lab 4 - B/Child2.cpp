#include "..\..\rt.h"

struct donutShop {
	char name[20];
	int amount;
};

int main() {
	struct donutShop donut;

	cout << "Child2 Process Creating the Pipeline\n";

	CPipe p2("Pipe2");

	cout << "Parent Process Creating Child Process to Read from Pipeline\n";

	strcpy_s(donut.name, "Sour Cream");
	p2.Write(&donut.name[0], sizeof(donut.name));
	cout << "Child2 Writing " << donut.name << " to pipeline\n";

	donut.amount = 12;
	p2.Write(&donut.amount, sizeof(donut.amount));
	cout << "Child2 Writing " << donut.amount << " to pipeline\n";

	Sleep(10000);

	return 0;
}