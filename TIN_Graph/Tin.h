#pragma once
#include"Node.h"
#include"LinkList.h"

using namespace std;

class TIN_Point :public Node
{
private:
	double lat, lng;//ÿ���������ֵ
	short nSingleEdgeCount;//���߼���
	myList edgeList;//�߱�

public:
	TIN_Point() :lat(0), lng(0) {}
	TIN_Point(int _id, double _x, double _y) :Node(_id), lat(_x), lng(_y) {}
	int getID() { return id; }
	void setID(int _id) { id = _id; }
	double getLat() { return lat; }
	double getLng () { return lng; }
	virtual void printData() { cout << id << " " << lat << " " << lng << endl; }
};

//class Edge
//{
//public:
//	int vertex, weight;
//	Edge();
//};

class TIN_Edge :public Node
{
public:
	TIN_Edge();//�޲γ�ʼ�����Ƿ���Ҫ�Ǹ����⣩
	TIN_Edge(int _id, TIN_Point*, TIN_Point*);//�����ֵ�ĳ�ʼ��
	~TIN_Edge();
	int getID() { return id; }
	virtual void printData();
	TIN_Point* getVertex1() { return pVertexE[0]; }
	TIN_Point* getVertex2() { return pVertexE[1]; }

private:
	TIN_Point * pVertexE[2];//��¼�˵��ָ��
	Triangle  * pTri;//ָ�������ε�ָ�룿��
	int nTri;//�ñ������������εĵڼ����ߣ���
	double length;//����·�߳���
};

class Triangle :public Node
{
private:
	TIN_Point * pVertexT[3];//�����ζ���ָ��
	TIN_Edge  * pEdgeT[3];
	//Triangle  * pAdjTri[3];//����������ָ��
	//int nTri[3];//���߷ֱ������������εĵڼ�����

public:
	Triangle();
	Triangle(int _id, TIN_Edge *, TIN_Edge *, TIN_Edge *);
	~Triangle();
	double getArea();//����ÿ�������ε����
	virtual void printData();
};

//class Graph
//{
//protected:
//	int amount;
//	vector<Edge> * edges;
//	bool * visited;
//public:
//	int * dist;
//	Graph(int input_n);
//	~Graph();
//	void insert(int x, int y, int weight);
//	void dijkstra(int nVStart);
//};

class TIN_Graph
{
private:
	myList lPoint;//�㼯
	myList lEdge;//�߼�
	myList lTriangle;//���Ǽ�

	int nAmount;//�ܹ��ĵ���
	myList * EdgeListArray;//�ڽӱ�
	bool * visited;//�������飬�����·�㷨�з�������
public:
	int * dist;//��ʼ��㵽��������ľ���
	TIN_Graph();
	~TIN_Graph();
};