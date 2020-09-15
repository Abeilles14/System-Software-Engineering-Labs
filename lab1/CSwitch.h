#ifndef   __CSwitch__
#define   __CSwitch__

class CSwitch {

private:
	int state;

public:
	// Constructors
	CSwitch();
	~CSwitch();

	// Accessors
	int getState();
	void print();

	// Mutators
	void turnon();
	void turnoff();
};

#endif