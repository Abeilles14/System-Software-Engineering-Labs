#ifndef __CList__ 
#define __CList__

struct Node {
	struct Node* next;
	int data;
};

template <class T> class CList {
private:
	Node* ptr;	// pointer to 1st node in list

public:
	CList();		// set ptr to null
	~CList();
	void insertNode(T new_data);	// add new node at end of list
	void deleteNode();	// delete node at end of list
	T getData(int index);		// get data from nth item in list
};

#endif
