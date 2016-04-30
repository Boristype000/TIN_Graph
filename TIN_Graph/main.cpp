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

	/*myList tPointList;
	int tID;
	double tX, tY;
	int tC = 0;
	while (tC != -1)
	{
		cin >> tID >> tX >> tY;
		TIN_Point *tPoint=new TIN_Point(tID, tX, tY);
		tPointList.push_back(tPoint);
		cin >> tC;
	}
	tPointList.output();
	tPointList.sort();
	tPointList.output();*/

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
	int n;
	cin >> n;

	double tX, tY;
	TIN_Graph testGraph;
	for (int i = 0; i < n; i++)
	{
		cin >> tX >> tY;
		TIN_Point * temp = new TIN_Point(tX, tY);
		testGraph.insertPoint(temp);
	}
	testGraph.buildTIN();

	cout << endl;

	testGraph.printPoint();

	cout << endl;

	testGraph.printTri();

	cout << testGraph.nTri;

	cout << endl<<endl;

	//testGraph.printEdgeCount();

	//testGraph.printUnUsedPoint();


	system("pause");
	return 0;
 }