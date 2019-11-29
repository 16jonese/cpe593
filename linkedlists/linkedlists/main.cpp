/*
Author: Ethan Jones
Pledge: I pledge my honor that I have abided by the stevens honor system
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<fstream>
#include<sstream>

using namespace std;

class LinkedList {
private:
	class Node {
	public:
		int val;
		Node* next;
		Node(int v, Node* next) : val(v), next(next) {}
	};

	Node* head;

	Node* tail() {
		Node* p = head;
		if (!p)
			return NULL;
		for (; p->next; p = p->next)
			;
		return p;
	}

public:
	LinkedList() {
		head = NULL;
	}
	void addStart(int v) {
		head = new Node(v, head);
	}

	void addEnd(int  v) {
		Node* temp = new Node(v, NULL);
		if (!head) {
			head = temp;
			return;
		}
		tail()->next = temp;
	}

	void insert(int pos, int v) {
		if (pos < 0 || pos >= size())
			throw "position not in bounds of the list.";
		if (!head)
			head = new Node(v, NULL);
		else if (pos == 0)
			addStart(v);
		else {
			Node* p = head;
			while (pos > 1 && p->next != NULL) {
				p = p->next;
				pos--;
			}
			p->next = new Node(v, p->next);
		}
	}

	int removeAt(int pos) {
		if (!head)
			throw "nothing in the list to remove";
		if (pos == 0)
			return removeStart();
		Node* p = head;
		Node* temp;
		while (pos > 1 && p->next) {
			p = p->next;
			pos--;
		}
		if (!p->next)
			throw "position not in bounds";
		temp = p->next;
		if (!temp->next) {
			int data = temp->val;
			p->next = NULL;
			return data;
		}
		else {
			p->next = temp->next;
			return temp->val;
		}
	}

	int removeStart() {
		if (!head)
			throw "nothing in the linked list to remove.";
		else {
			Node* temp = head;
			head = head->next;
			return temp->val;
		}
	}

	int removeEnd() {
		if (!head)
			throw "Nothing in the list to remove.";
		else if (!head->next) {
			int v = tail()->val;
			return v;
		}

	}

	int get(int pos) {
		if (!head)
			throw "Nothing in the list to search from.";
		Node* p = head;
		while (pos > 0 && p->next) {
			p = p->next;
			pos--;
		}
		if (pos > 0)
			throw "position not in the bounds of the list.";
		return p->val;
	}

	int size() {
		int size = 0;
		if (!head)
			return size;
		else {
			size++;
			Node* p = head;
			while (p->next) {
				size++;
				p = p->next;
			}
			return size;
		}
	}

	friend ostream& operator <<(ostream& s, const LinkedList& list) {
		Node* p = list.head;
		if (!p)
			return s;
		else {
			for (; p->next; p = p->next)
				s << p->val << ' ';
			s << p->val << ' ';
			return s;
		}
	}
};

//Declaring the linked lists as global variables
LinkedList listA;
LinkedList listB;

//Initates the hw5.dat file and reads in the integers to the linked list A
void initiateFile(const char* filename) {
	int data = 0;
	ifstream file;
	file.open(filename);
	if (!file)
		throw "file not found";
	while (file >> data) {
		listA.addEnd(data);
	}
	if (listA.size() == 0)
		throw "The File is empty.";
}

//Checks for the even numbers in the linked list B and adds the value to B
//While simultaneously removing it from A
void checkEvens() {
	int data;
	int pos = 0;
	int size = listA.size();
	while (pos < size) {
		data = listA.get(pos);
		if (data % 2 == 0) {
			listB.addEnd(listA.removeAt(pos));
			pos--;
			size--;
		}
		pos++;
	}
}

//Combines the two linked lists into A, where if the index in A is even, it takes a value from B
//and Places it there. If it reaches the end of A, it will continue to Add to A until B is empty.
void combine() {
	int sizeA = listA.size();
	int sizeB = listB.size();
	int posB = 0;
	for (int i = 0; i < sizeA; i++) {
		if (posB < sizeB && i % 2 == 0) {
			listA.insert(i, listB.get(posB));
			posB++;
			sizeA++;
		}
	}
	while (posB < sizeB) {
		listA.addEnd(listB.get(posB));
		posB++;
	}
}

int main() {
	const char* filename = "hw5.dat";
	initiateFile(filename);
	cout << listA << " " << endl;
	checkEvens();
	cout << "After checking for evens - ";
	cout << " list A: " << listA << " " ;
	cout << " list B: " << listB << " " << endl;
	combine();
	cout << "After properly combining A and B - ";
	cout << " list A: " << listA << " " << endl;
	cin.get();
}
