#pragma once
#include"Node.h"
#include"LinkList.h"
#include<cassert>

using namespace std;
class myQueue :public myList
	//链式队列
{
public:
	myQueue():myList(){}
	~myQueue() {/* remove(); */}//析构函数先析构派生类再析构基类



	bool isEmpty() { return (head == NULL ? true : false); }

	void pop_front()
	{
		assert(!isEmpty());
		Node* pDel = head;
		head = head->next;
		head->prev = NULL;
		delete pDel;
	}
};