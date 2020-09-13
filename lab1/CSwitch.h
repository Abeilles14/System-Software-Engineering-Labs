#pragma once

#ifndef   __CSwitch__
#define   __CSwitch__

class CSwitch {

public:
	CSwitch();
	~CSwitch();

	void turnon();
	void turnoff();
	void print();

	int getState();

private:
	int state;
};

#endif