#pragma once
#include"Node.h"
#include"LinkList.h"

using namespace std;

class TIN_Point :public Node
{
private:
	double lat, lng;//每个点的坐标值
	short nSingleEdgeCount;//单边计数
	myList edgeList;//边表

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
	TIN_Edge();//无参初始化（是否需要是个问题）
	TIN_Edge(int _id, TIN_Point*, TIN_Point*);//输入点值的初始化
	~TIN_Edge();
	int getID() { return id; }
	virtual void printData();
	TIN_Point* getVertex1() { return pVertexE[0]; }
	TIN_Point* getVertex2() { return pVertexE[1]; }

private:
	TIN_Point * pVertexE[2];//记录端点的指针
	Triangle  * pTri;//指向三角形的指针？？
	int nTri;//该边是相邻三角形的第几条边？？
	double length;//该条路线长度
};

class Triangle :public Node
{
private:
	TIN_Point * pVertexT[3];//三角形顶点指针
	TIN_Edge  * pEdgeT[3];
	//Triangle  * pAdjTri[3];//相邻三角形指针
	//int nTri[3];//三边分别是相邻三角形的第几条边

public:
	Triangle();
	Triangle(int _id, TIN_Edge *, TIN_Edge *, TIN_Edge *);
	~Triangle();
	double getArea();//计算每个三角形的面积
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
	myList lPoint;//点集
	myList lEdge;//边集
	myList lTriangle;//三角集

	int nAmount;//总共的点数
	myList * EdgeListArray;//邻接表
	bool * visited;//访问数组，在最短路算法中发挥作用
public:
	int * dist;//起始点点到其它各点的距离
	TIN_Graph();
	~TIN_Graph();
};