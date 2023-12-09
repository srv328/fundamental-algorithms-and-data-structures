#pragma once
#include <string>

struct list_elem {
	int key;
	list_elem* next, * prev;
};

list_elem* list_init()
{
	list_elem* root = nullptr;
	return root;
}

void list_insert(list_elem*& head)
{
	list_elem* newNode = new list_elem;
	newNode->next = nullptr;
	newNode->prev = nullptr;

	if (head == nullptr) {
		head = newNode;
		head->next = head;
		head->prev = head;
		head->key = 0;
	}
	else {
		newNode->key = head->prev->key + 1;
		newNode->next = head;
		newNode->prev = head->prev;
		head->prev->next = newNode;
		head->prev = newNode;
	}
}

void remove(list_elem*& head) {
	if (head == nullptr) {
		return;
	}
	else if (head->next == head) {
		delete head;
		head = nullptr;
		return;
	}

	list_elem* last = head->prev;
	list_elem* prev = last->prev;

	prev->next = head;
	head->prev = prev;
	delete last;

}


void list_erase(list_elem*& head) {
	if (head == nullptr) {
		return;
	}

	list_elem* current = head;
	list_elem* nextNode = nullptr;

	do {
		nextNode = current->next;
		delete current;
		current = nextNode;
	} while (current != head);

	head = nullptr;
}

void print_list(list_elem* root) {
	
	if (root != nullptr) {
		list_elem* temp = root;

		do {
			std::cout << "[" << temp->key << "]";
			temp = temp->next;
			if (temp != root) std::cout << "->";
		} while (temp != root);
	}
}

