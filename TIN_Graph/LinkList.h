#pragma once
#include <string>
#include"Node.h"

using namespace std;




class myList
{
protected:
	Node* head;//��ͷָ��
	int size;//������
	Node* tail;//��βָ��
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

	//Node* half_search(int _id, Node*, Node*, Node*);

public:
	myList() { head = NULL; tail = NULL; size = 0; }
	//myList(myList &);
	 ~myList() { remove(); }

	void insert(Node *_pNode)//���뺯��
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
		if (index == getSize() - 1)
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


	//Node* search_half(int, Node*);
};
