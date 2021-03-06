#pragma once
#include<iostream>

using namespace std;
class Node
{
protected:
	int id;
public:
	Node* next;
	Node* prev;
	Node(int _id) { id = _id; next = NULL; prev = NULL; }
	Node() { id = 0; next = NULL; prev = NULL; }
	virtual ~Node(){}
	int getID() { return id; }
	void setID(int _id) { id = _id; }
	virtual void printData()
	{
		cout << id << " ";
	}
	virtual double sortSeed() { return id; }


	//virtual double searchSeed() { return id; }

};