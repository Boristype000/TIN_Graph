#pragma once
#include"Node.h"
#include"LinkList.h"
#include<cassert>

using namespace std;
class myQueue :public myList
	//��ʽ����
{
public:
	myQueue():myList(){}
	~myQueue() {/* remove(); */}//������������������������������



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