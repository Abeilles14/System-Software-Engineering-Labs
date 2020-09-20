#include <iostream>
#include "CList.h"

using namespace std;

template <class T> CList<T>::CList() {
	ptr = NULL;		// set ptr node to null

	cout << "CList constructor called, list is null\n";
}

template <class T> CList<T>::~CList() {
	cout << "CList destructor called\n";
}

template <class T> void CList<T>::insertNode(T new_data) {
	Node* new_node = new Node();

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
	Node* temp = new Node();

	if (ptr != NULL) {
		cout << "CList node with data " << ptr->data << " deleted\n";

		temp = ptr;
		ptr = ptr->next;	// move ptr down
		temp = NULL;		// delete node
	}
}

template <class T> T CList<T>::getData(int index) {
	Node* current = ptr;

	if (ptr == NULL) {
		return NULL;
	}

	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	cout << "Data at CList node " << index << " = " << current->data << "\n";

	return current->data;
}