#ifndef   __CBulb__
#define   __CBulb__

class CBulb {

private:
	int state;		// Enables state of bulb
	int watts;

public:
	// Constructors
	CBulb(int watts_value);
	CBulb();
	~CBulb();

	// Accessors
	int getPower();
	int getstate();
	void print();

	// Mutators
	// void setstate(int value);
	void on();
	void off();
	void setwatts(int watts_value);
};

#endif 
