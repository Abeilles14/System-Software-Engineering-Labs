#ifndef __List__ 
#define __List__

struct Node {
	struct Node* next;
	int data;
};

class CList {
private:
	Node* ptr;	// pointer to 1st node in list

public:
	CList();		// set ptr to null
	~CList();
	void insertNode(int new_data);	// add new node at end of list
	void deleteNode();	// delete node at end of list
	int getData(int index);		// get data from nth item in list
};

#endif
