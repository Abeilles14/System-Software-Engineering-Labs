#include <iostream>
#include "CList.h"

using namespace std;

CList::CList() {
	ptr = NULL;		// set ptr node to null

	cout << "CList constructor called, list is null\n";
}

CList::~CList() {
	cout << "CList destructor called\n";
}

void CList::insertNode(int new_data) {
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

void CList::deleteNode() {
	Node* temp = new Node();

	if (ptr != NULL) {
		cout << "CList node with data " << ptr->data << " deleted\n";

		temp = ptr;
		ptr = ptr->next;	// move ptr down
		temp = NULL;		// delete node
	}
}

int CList::getData(int index) {
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