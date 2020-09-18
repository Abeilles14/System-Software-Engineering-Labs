#include <iostream>
#include "CList.h"

using namespace std;

CList::CList() {
	ptr = NULL;		// set ptr to null

	cout << "CList constructor calledc\n";
}

CList::~CList() {
	cout << "CList destructor called\n";
}

void CList::insertNode(int new_data) {
	Node* new_node = new Node();

	if (ptr == NULL)		// if list is NULL
	{
		ptr = new_node;		// create new node
	}

	new_node->data = new_data;
	new_node->next = ptr;
	ptr = new_node;

	cout << "Node added to CList\n";
}

void CList::deleteNode() {
	Node* temp;

	if (ptr != NULL) {
		temp = ptr->next;
	}

	cout << "CList node deleted\n";
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