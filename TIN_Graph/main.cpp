#include"LinkList.h"
#include<iostream>
#include"Tin.h"
#include"Queue.h"
using namespace std;

int main()
{
	//myList testList;
	//int temp = 0;
	//while (temp != -1)
	//{
	//	cin >> temp;
	//	Node *tNode = new Node(temp);
	//	testList.insert(tNode);
	//}
	//testList.output();
	//cout << endl;
	//cout << testList.getLength()<< endl;

	myList tPointList;
	int tID;
	double tX, tY;
	int tC = 0;
	while (tC != -1)
	{
		cin >> tID >> tX >> tY;
		TIN_Point *tPoint=new TIN_Point(tID, tX, tY);
		tPointList.insert(tPoint);
		cin >> tC;
	}
	tPointList.output();
	tPointList.sort_merge();
	tPointList.output();

	/*myQueue tQueue;
	for (int i = 0; i < 5; i++)
	{
		int tID; double tX, tY;
		cin >> tID >> tX >> tY;
		Node *tPoint = new TIN_Point(tID, tX, tY);
		tQueue.push_back(tPoint);
	}
	tQueue.output();
	cout << endl;
	tQueue.pop_front();
	tQueue.output();*/


	system("pause");
	return 0;
 }