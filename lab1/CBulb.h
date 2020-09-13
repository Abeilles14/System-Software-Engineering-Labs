#pragma once

#ifndef   __CBulb__
#define   __CBulb__

class CBulb {

public:
	CBulb(int watts_value);
	CBulb();
	~CBulb();

	void print();
	//void setstate(int value);
	void setwatts(int watts_value);
	void on();
	void off();

	int getPower();
	int getstate();

private:
	int state;		//enables state of bulb
	int watts;

};

#endif 
