#pragma once
#include <string>
#include"Node.h"

using namespace std;




class myList
{
protected:
	Node* head;//表头指针
	Node* tail;//表尾指针
	int size;//链表长度
	void remove()
	{
		if (head != NULL)
		{
			Node* pMove = head;
			while (pMove != NULL)
			{
				Node *pDel = pMove;
				pMove = pMove->next;
				delete pDel;
			}
		}
		else
		{
			return;
		}
	}
	Node* mergeSortedList(Node* pLeft, Node * pRight)
	{

		Node tHead, *ptLeft = &tHead, *ptRight = pRight;
		//定义临时头指针，前向指针指向左链表的头，为了方便插入操作
		tHead.next = pLeft;
		while (ptLeft->next != NULL && ptRight != NULL)
		{
			if (ptLeft->next->sortSeed() >= ptRight->sortSeed())
				//根据虚函数sortSeed获取排序种子
			{
				pRight = ptRight->next;
				ptRight->next = ptLeft->next;
				ptLeft->next = ptRight;
				ptLeft = ptRight;
				ptRight = pRight;
				//以上的操作是为了把右链表的头指针扯下来安到左链表头
			}
			else
			{
				ptLeft = ptLeft->next;
			}
		}
		if (ptLeft->next == NULL)
		{
			//如果右链表还有剩，直接安到左链表的后头
			ptLeft->next = ptRight;
		}

		return tHead.next;

	}
	Node* merge_sort(Node* pHead)
	{
		if (pHead == NULL || pHead->next == NULL)
		{
			return pHead;
		}//如果传入的链表只有一个或没有元素，直接返回

		Node *pFast = pHead, *pSlow = pHead;
		//用快慢指针来找寻链表中间的结点位置
		while (pFast->next != NULL && pFast->next->next != NULL)
		{
			pFast = pFast->next->next;
			pSlow = pSlow->next;
		}
		Node *pNewR = pSlow->next;
		pSlow->next = NULL;
		//将原链表在pSlow处截断

		Node *pLeft = merge_sort(pHead);
		Node *pRight = merge_sort(pNewR);
		//对产生的两个新链表递归
		return mergeSortedList(pLeft, pRight);
		//把递归返回的两个排好序的链表进行组合
	}
	//Node* half_search(int _id, Node*, Node*, Node*);

public:
	myList() { head = NULL; tail = NULL; size = 0; }
	//myList(myList &);
	 ~myList() { remove(); }//基类的析构一定要virtual！！

	void push_back(Node *_pNode)//插入函数
	{
		if (head == NULL)
		{
			head = _pNode;
			size++;
			tail = _pNode;
			return;
		}
		tail->next = _pNode;
		_pNode->prev = tail;
		tail = _pNode;
		size++;
		
	}
	void output()
	{
		if (head==NULL)return;
		Node *pMove = head;
		while (pMove!=NULL)
		{
			pMove->printData();
			pMove = pMove->next;
		}
	}
	void delete_node(int index)
	{
		if (head == NULL)
		{
			return;
		}
		Node *pMove = head;//使移动指针指向头结点
		int count = 0;

		if (index == 0)
			//处理删除头结点情况
		{
			head = head->next;
			head->prev = NULL;
			delete pMove;
			return;
		}
		if (index == size - 1)
			//处理删除尾结点情况
		{
			pMove = tail;
			tail = tail->prev;
			tail->next = NULL;
			delete pMove;
			return;
		}
		while (pMove->next != NULL && count < index - 1)
		{
			pMove = pMove->next;
			count++;
		}
		if (count == index - 1 && pMove->next != NULL)
		{
			if (pMove->next->next == NULL)
			{
				tail = pMove;
				tail->next = NULL;
			}
			Node *delete_node = pMove->next;
			pMove->next = delete_node->next;
			delete delete_node;
			size--;
		}
	}
	int getSize() { return size; }

	Node* front() { return head; }
	Node* back() { return tail; }

	void sort()
	{
		head = merge_sort(head);

		//下面代码为了理顺前向指针
		head->prev = NULL;
		Node *pMove = head;
		while (pMove != NULL)
		{
			if (pMove->next == NULL)
			{
				tail = pMove;
				break;
			}
			pMove->next->prev = pMove;
			pMove = pMove->next;

		}
	}


	//Node* search_half(int, Node*);
};
