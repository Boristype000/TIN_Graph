#pragma once
#include <string>
#include"Node.h"

using namespace std;




class myList
{
protected:
	Node* head;//��ͷָ��
	Node* tail;//��βָ��
	int size;//������
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
		//������ʱͷָ�룬ǰ��ָ��ָ���������ͷ��Ϊ�˷���������
		tHead.next = pLeft;
		while (ptLeft->next != NULL && ptRight != NULL)
		{
			if (ptLeft->next->sortSeed() >= ptRight->sortSeed())
				//�����麯��sortSeed��ȡ��������
			{
				pRight = ptRight->next;
				ptRight->next = ptLeft->next;
				ptLeft->next = ptRight;
				ptLeft = ptRight;
				ptRight = pRight;
				//���ϵĲ�����Ϊ�˰��������ͷָ�볶��������������ͷ
			}
			else
			{
				ptLeft = ptLeft->next;
			}
		}
		if (ptLeft->next == NULL)
		{
			//�����������ʣ��ֱ�Ӱ���������ĺ�ͷ
			ptLeft->next = ptRight;
		}

		return tHead.next;

	}
	Node* merge_sort(Node* pHead)
	{
		if (pHead == NULL || pHead->next == NULL)
		{
			return pHead;
		}//������������ֻ��һ����û��Ԫ�أ�ֱ�ӷ���

		Node *pFast = pHead, *pSlow = pHead;
		//�ÿ���ָ������Ѱ�����м�Ľ��λ��
		while (pFast->next != NULL && pFast->next->next != NULL)
		{
			pFast = pFast->next->next;
			pSlow = pSlow->next;
		}
		Node *pNewR = pSlow->next;
		pSlow->next = NULL;
		//��ԭ������pSlow���ض�

		Node *pLeft = merge_sort(pHead);
		Node *pRight = merge_sort(pNewR);
		//�Բ���������������ݹ�
		return mergeSortedList(pLeft, pRight);
		//�ѵݹ鷵�ص������ź��������������
	}
	//Node* half_search(int _id, Node*, Node*, Node*);

public:
	myList() { head = NULL; tail = NULL; size = 0; }
	//myList(myList &);
	 ~myList() { remove(); }//���������һ��Ҫvirtual����

	void push_back(Node *_pNode)//���뺯��
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
		Node *pMove = head;//ʹ�ƶ�ָ��ָ��ͷ���
		int count = 0;

		if (index == 0)
			//����ɾ��ͷ������
		{
			head = head->next;
			head->prev = NULL;
			delete pMove;
			return;
		}
		if (index == size - 1)
			//����ɾ��β������
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

		//�������Ϊ����˳ǰ��ָ��
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
