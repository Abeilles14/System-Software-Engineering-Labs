#ifndef __CList__ 
#define __CList__

#include <iostream>

using namespace std;

template <class T> struct Node {
	struct Node* next;
	T data;
};

template <class T> class CList {
private:
	Node<T>* ptr;	// pointer to 1st node in list

public:
	CList();		// set ptr to null
	~CList();
	void insertNode(T new_data);	// add new node at end of list
	void deleteNode();				// delete node at end of list
	T getData(int index);			// get data from nth item in list
};

// Template class implementation

template <class T> CList<T>::CList() {
	ptr = NULL;		// set ptr node to null

	cout << "CList constructor called, list is null\n";
}

template <class T> CList<T>::~CList() {
	cout << "CList destructor called\n";
}

template <class T> void CList<T>::insertNode(T new_data) {
	Node<T>* new_node = new Node<T>();

	if (ptr == NULL) {
		ptr = new_node;
		ptr->data = new_data;
		ptr->next = NULL;
	}
	else {
		new_node->data = ptr->data;		// replace ptr by node
		new_node->next = ptr->next;
		ptr->data = new_data;			// place ptr at head with new data
		ptr->next = new_node;
	}

	cout << "Node data " << ptr->data << " added to CList\n";
}

template <class T> void CList<T>::deleteNode() {
	Node<T>* temp = new Node<T>();

	if (ptr != NULL) {
		cout << "CList node with data " << ptr->data << " deleted\n";

		temp = ptr;
		ptr = ptr->next;	// move ptr down
		temp = NULL;		// delete node
	}
}

template <class T> T CList<T>::getData(int index) {
	Node<T>* current = ptr;

	if (ptr == NULL) {
		return NULL;
	}

	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	cout << "Data at CList node " << index << " = " << current->data << "\n";

	return current->data;
}

#endif
