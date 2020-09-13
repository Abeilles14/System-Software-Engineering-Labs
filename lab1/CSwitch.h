#pragma once

#ifndef   __CSwitch__
#define   __CSwitch__

class CSwitch {

public:
	CSwitch();
	~CSwitch();

	void turnon();
	void turnoff();
	int getState();
	void print();

private:
	int state;
};

#endif