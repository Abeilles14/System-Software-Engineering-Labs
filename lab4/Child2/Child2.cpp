#include "..\..\rt.h"

struct example {
	int x;
	float y;
};

int i;
int array1[10];

char name[15];
struct example mystruct;

int main() {

	int x;

	printf("Child Process 2 Opening Pipeline 2\n");
	CPipe p1("MyPipe2", 1024);		// create pipes size 1024

	p1.Read(&i, sizeof(i));			// read int i from pipe and store value 
	cout << "Child Process 2 read integer = " << i << " from Pipeline 2\n";

	p1.Read(&array1[0], sizeof(array1));		// read array of integers and store values

	printf("Child Process 2 read array = ");
	for (x = 0; x < sizeof(array1) / sizeof(array1[0]); x++) {
		cout << " " << array1[x];
	}

	putchar('\n');

	p1.Read(&name[0], sizeof(name));		// read string frome pipe and store values
	cout << "Child Process 2 read string = " << name << ", from Pipeline 2\n";

	p1.Read(&mystruct, sizeof(mystruct));
	cout << "Child Process 2 read [" << mystruct.x << "," << mystruct.y << "] from Pipeline 2\n";

	Sleep(4000);

	return 0;
}